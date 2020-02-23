#include "Tray.h"

Tray::Tray(int traymotorport, 
           int traymotor1port, 
           vex::triport::port *zero_switch_port, 
           vex::triport::port *cube_switch_port,
           vex::brain *brain_p) : 
  traymotor(vexDeviceGetByIndex(traymotorport - 1)), 
  traymotor1(vexDeviceGetByIndex(traymotor1port - 1)), 
  zero_switch(*zero_switch_port), 
  cube_switch(*cube_switch_port),
  brain_ptr(brain_p),
  tray_pid(0, P, I, D, -12000, 12000, -12000, 12000),
  traymotor_base(0.0)
{
}

void Tray::movePID()
{
  setMotors((int32_t) tray_pid.compute(getTrayRotation()));
}

void Tray::moveConst(int32_t vel)
{
  setMotors(vel);
}

void Tray::movebyJoy(int32_t vel)
{
  setMotors(vel);
  brain_ptr->Screen.clearLine(0,vex::color::black);
  brain_ptr->Screen.clearLine(1,vex::color::black);
  brain_ptr->Screen.setCursor(1,0);
  brain_ptr->Screen.print("Arm rotation: %f degrees", getTrayRotation());
  brain_ptr->Screen.setCursor(2,0);
  // Brain.Screen.print("Claw rotation: %f degrees",motor_claw.rotation(vex::rotationUnits::deg));
}

void Tray::zeroEncoder()
{
  traymotor_base = vexDeviceMotorPositionGet(traymotor);
}

void Tray::update(System_State state, bool go)
{
  if(state == TRAY_ZERO)
  {
    moveConst(-6000);
  }
  if(state == BASE_TRAY){
    if(go){
      movePID();
    }
  }
  else if (state == BASE_ARM || 
          state == ARM1 || 
          state == ARM2 || 
          state == POSITION_CUBES ||
          state == ARM_ZERO ||
          state == TRAY_VERTICAL)
  {
    movePID();
  }
  else if (state == UNFOLD_ARM_ZERO || UNFOLD)
  {
    moveConst(0);
  }
}

int32_t Tray::getTrayRotation()
{
  uint32_t time;
  return vexDeviceMotorPositionRawGet(traymotor, &time) - traymotor_base;
}

bool Tray::getLimitSwitch()
{
  return zero_switch.pressing();
}

bool Tray::getCubeSwitch()
{
  return cube_switch.pressing();
}

void Tray::setMotors(int32_t input)
{
    vexDeviceMotorVoltageSet(traymotor, input);
    vexDeviceMotorVoltageSet(traymotor1, -input);  
}

void Tray::setPIDBounds(int32_t min_power, int32_t max_power)
{
  tray_pid.setBounds(min_power, max_power);
  tray_pid.setIBounds(min_power, max_power);
}

void Tray::setTargetPos(int32_t target)
{
  tray_pid.setTarget(target);
}

void Tray::stopPID()
{
  tray_pid.stop();
}

int32_t Tray::getSetPosition(){
  return tray_pid.getTarget();
}

void Tray::updateAuto(Auto_State state)
{
  if(state == TRAY_VERTICAL_AUTO ||
     state == OUTTAKE)
  {
    movePID();
  }
  else
  {
    moveConst(0);
  }
}
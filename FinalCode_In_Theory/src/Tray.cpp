#include "Tray.h"

Tray::Tray(int traymotorport, 
           int traymotor1port, 
           vex::triport::port *zero_switch_port, 
           vex::triport::port *cube_switch_port,
           vex::brain *brain_p) : 
  traymotor(vexDeviceGetByIndex(traymotorport-1)), 
  traymotor1(vexDeviceGetByIndex(traymotor1port-1)),
  zero_switch(*zero_switch_port),
  cube_switch(*cube_switch_port),
  brain_ptr(brain_p),
  traymotor_base(0)
{
}

bool Tray::movePosition(double position)
{
  double error = position - getTrayRotation();
  
  if(std::abs(error)>ERROR_THRESHOLD)
  {
    vexDeviceMotorVoltageSet(traymotor, P*error);
    vexDeviceMotorVoltageSet(traymotor1, -P*error);
    
    brain_ptr->Screen.clearLine(0,vex::color::black);
    brain_ptr->Screen.clearLine(1,vex::color::black);
    brain_ptr->Screen.clearLine(2,vex::color::black);
    brain_ptr->Screen.setCursor(1,0);
    //  Brain.Screen.print("Position: ",error);

    brain_ptr->Screen.setCursor(2,0);
    brain_ptr->Screen.print("Arm rotation: %f degrees", getTrayRotation());

    return false;  
  }

  vexDeviceMotorVoltageSet(traymotor, 0);
  vexDeviceMotorVoltageSet(traymotor1, 0);
  return true;
}

void Tray::moveConst(int32_t vel)
{
  vexDeviceMotorVoltageSet(traymotor, vel);
  vexDeviceMotorVoltageSet(traymotor1, -vel);
}

void Tray::movebyJoy(int32_t vel)
{
  vexDeviceMotorVoltageSet(traymotor, vel);
  vexDeviceMotorVoltageSet(traymotor1, -vel);
  brain_ptr->Screen.clearLine(0,vex::color::black);
  brain_ptr->Screen.clearLine(1,vex::color::black);
  brain_ptr->Screen.setCursor(1,0);
  brain_ptr->Screen.print("Arm rotation: %f degrees", getTrayRotation());
  brain_ptr->Screen.setCursor(2,0);
  // Brain.Screen.print("Claw rotation: %f degrees",motor_claw.rotation(vex::rotationUnits::deg));
}

void Tray::zeroEncoder()
{
  uint32_t time;
  traymotor_base = vexDeviceMotorPositionRawGet(traymotor, &time);
}

void Tray::update(System_State state)
{
  if(state == TRAY_ZERO)
  {
    moveConst(-6000);
  }
  else if (state == BASE || 
          state == ARM1 || 
          state == ARM2 || 
          state == POSITION_CUBES )
  {
    movePosition(Ports::TRAY_BASE_POSITION);
  }
  else if (state == TRAY_VERTICAL)
  {
    movePosition(Ports::TRAY_VERTICAL_POSITION);
  }
}

int32_t Tray::getTrayRotation()
{
  uint32_t time;
  return vexDeviceMotorPositionRawGet(traymotor, &time) - traymotor_base;
}

bool Tray::getLimitSwitch()
{
  return zero_switch.value();
}

bool Tray::getCubeSwitch()
{
  return cube_switch.value();
}
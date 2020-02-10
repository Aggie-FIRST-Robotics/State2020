#include "Tray.h"

Tray::Tray(int traymotorport, 
           int traymotor1port, 
           int zero_switch_port, 
           int cube_switch_port,
           vex::brain *brain_p) : 
  traymotor(vexDeviceGetByIndex(traymotorport - 1)), 
  traymotor1(vexDeviceGetByIndex(traymotor1port - 1)), 
  zero_switch(zero_switch_port), 
  cube_switch(cube_switch_port),
  brain_ptr(brain_p),
  traymotor_base(0.0)
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
  traymotor_base = vexDeviceMotorPositionGet(traymotor);
}

bool Tray::update(System_State state)
{
  if(state == System_State::TRAY_ZERO) // TODO: potential bug here
  {
    if(!zero_switch.value()){
      moveConst(-6000);
    }
    else
    {
      zeroEncoder();
      return true;
    }
  }
  else if (state == System_State::BASE || 
          state == System_State::ARM1 || 
          state == System_State::ARM2 || 
          state == System_State::POSITION_CUBES )
  {
    return movePosition(Ports::TRAY_BASE_POSITION);
  }
  else if (state == System_State::TRAY_VERTICAL)
  {
      return movePosition(Ports::TRAY_VERTICAL_POSITION);
  }

  return false;
}

double Tray::getTrayRotation()
{
  return vexDeviceMotorPositionGet(traymotor) - traymotor_base;
}
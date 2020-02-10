#include "DriveTrain.h"

DriveTrain::DriveTrain(int topleftMotorport, 
            int toprightMotorport, 
            int bottomleftMotorport, 
            int bottomrightMotorport,
            vex::controller *controller_p) : 
  topleftMotor(vexDeviceGetByIndex(topleftMotorport - 1)), 
  toprightMotor(vexDeviceGetByIndex(toprightMotorport - 1)), 
  bottomleftMotor(vexDeviceGetByIndex(bottomleftMotorport - 1)), 
  bottomrightMotor(vexDeviceGetByIndex(bottomrightMotorport - 1)),
  controller_ptr(controller_p)
{
}

void DriveTrain::arcadeDrive(int32_t forward, int32_t turn)
{
  vexDeviceMotorVoltageSet(topleftMotor, forward+turn);
  vexDeviceMotorVoltageSet(toprightMotor, forward-turn);
  vexDeviceMotorVoltageSet(bottomleftMotor, forward+turn);
  vexDeviceMotorVoltageSet(bottomrightMotor, forward-turn);
}

void DriveTrain::RealDrive(int32_t left, int32_t right)
{
  vexDeviceMotorVoltageSet(topleftMotor, left);
  vexDeviceMotorVoltageSet(toprightMotor, right);
  vexDeviceMotorVoltageSet(bottomleftMotor, left);
  vexDeviceMotorVoltageSet(bottomrightMotor, right);
}

bool DriveTrain::update(DriveTrain_State state)
{
  if(state == DriveTrain_State::DRIVE)
  {
    arcadeDrive(JoystickAxis(*controller_ptr, joystick_config::FORWARD_AXIS), 
                JoystickAxis(*controller_ptr, joystick_config::TURN_AXIS));
    return true;
  }

  return false;
}
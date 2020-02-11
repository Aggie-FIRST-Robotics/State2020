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
  int32_t modifiedleft;
  int32_t modifiedright;

  if(abs(left)>0.05){
    modifiedleft = 0;
  }
  else{
    modifiedleft = left*left;
  }
  if(abs(right)>0.05){
    modifiedright = 0;
  }
  else{
    modifiedright = right*right;
  }
  vexDeviceMotorVoltageSet(topleftMotor, modifiedleft);
  vexDeviceMotorVoltageSet(toprightMotor, modifiedright);
  vexDeviceMotorVoltageSet(bottomleftMotor, modifiedleft);
  vexDeviceMotorVoltageSet(bottomrightMotor, modifiedright);
}

void DriveTrain::update(DriveTrain_State state)
{
  if(state == DRIVE)
  {
    RealDrive(JoystickAxis(*controller_ptr, joystick_config::FORWARD_AXIS), 
                JoystickAxis(*controller_ptr, joystick_config::TURN_AXIS));
  }
}
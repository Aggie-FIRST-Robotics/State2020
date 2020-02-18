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

  double left_scaled = left/127.0;
  double right_scaled = right/127.0;

  if(std::abs(left_scaled)<0.05){
    modifiedleft = 0;
  }
  else{
    modifiedleft = (int32_t)(left_scaled*left_scaled*12000.0*(left_scaled >= 0 ? -1 : 1));
  }
  if(std::abs(right_scaled)<0.05){
    modifiedright = 0;
  }
  else{
    modifiedright = (int32_t)(right_scaled*right_scaled*12000.0*(right_scaled >= 0 ? 1 : -1));
  }

  Brain.Screen.printAt(10, 150, "%d", modifiedleft);
  vexDeviceMotorVoltageSet(topleftMotor, modifiedleft);
  vexDeviceMotorVoltageSet(toprightMotor, modifiedright);
  vexDeviceMotorVoltageSet(bottomleftMotor, modifiedleft);
  vexDeviceMotorVoltageSet(bottomrightMotor, modifiedright);
}

void DriveTrain::update(DriveTrain_State state)
{
  if(state == DRIVE)
  {
    RealDrive(JoystickAxis(*controller_ptr, joystick_config::LEFT_AXIS), 
                JoystickAxis(*controller_ptr, joystick_config::RIGHT_AXIS));
  }
  if(state == DRIVE_BACK_STATE){
    if(JoystickButtonPressed(*controller_ptr, joystick_config::OUTTAKE_BUTTON)){
        RealDrive(-0.2*127, -0.2*127);
    }
  }
}



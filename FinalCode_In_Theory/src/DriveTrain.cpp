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
  controller_ptr(controller_p),
  auto_drive(VEL_P, VEL_I, VEL_D, POS_P, POS_I, POS_D)
{
}

void DriveTrain::arcadeDrive(int32_t forward, int32_t turn)
{
  int32_t modifiedleft;
  int32_t modifiedright;

  double left_scaled = (forward + turn)/127.0;
  if(left_scaled > 1.0)
  {
    left_scaled = 1.0;
  }
  else if(left_scaled < -1.0)
  {
    left_scaled = -1.0;
  }
  double right_scaled = (forward - turn)/127.0;
  if(right_scaled > 1.0)
  {
    right_scaled = 1.0;
  }
  else if(right_scaled < -1.0)
  {
    right_scaled = -1.0;
  }

  if(std::abs(left_scaled)<0.05){
    modifiedleft = 0;
  }
  else{
    modifiedleft = (int32_t)(left_scaled*left_scaled*12000.0*(left_scaled >= 0 ? 1 : -1));
  }
  if(std::abs(right_scaled)<0.05){
    modifiedright = 0;
  }
  else{
    modifiedright = (int32_t)(right_scaled*right_scaled*12000.0*(right_scaled >= 0 ? 1 : -1));
  }

  setPower(modifiedleft, modifiedright);
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
    modifiedleft = (int32_t)(left_scaled*left_scaled*12000.0*(left_scaled >= 0 ? 1 : -1));
  }
  if(std::abs(right_scaled)<0.05){
    modifiedright = 0;
  }
  else{
    modifiedright = (int32_t)(right_scaled*right_scaled*12000.0*(right_scaled >= 0 ? 1 : -1));
  }

  setPower(modifiedleft, modifiedright);
}

void DriveTrain::setPower(int32_t left, int32_t right)
{
  vexDeviceMotorVoltageSet(topleftMotor, -left);
  vexDeviceMotorVoltageSet(toprightMotor, right);
  vexDeviceMotorVoltageSet(bottomleftMotor, -left);
  vexDeviceMotorVoltageSet(bottomrightMotor, right);
}

void DriveTrain::update(DriveTrain_State state)
{
  if(state == DRIVE)
  {
    arcadeDrive(JoystickAxis(*controller_ptr, joystick_config::FORWARD_AXIS), 
                JoystickAxis(*controller_ptr, joystick_config::TURN_AXIS));
  }
  if(state == DRIVE_BACK_STATE){
    if(JoystickButtonPressed(*controller_ptr, joystick_config::OUTTAKE_BUTTON)){
        setPower(-4000, -4000);
    }
  }
}

AutoDrive &DriveTrain::getAutoDrive()
{
  return auto_drive;
}

int32_t DriveTrain::getLeftEncoder()
{
  uint32_t time;
  return -vexDeviceMotorPositionRawGet(topleftMotor, &time);
}

int32_t DriveTrain::getRightEncoder()
{
  uint32_t time;
  return vexDeviceMotorPositionRawGet(toprightMotor, &time);
}
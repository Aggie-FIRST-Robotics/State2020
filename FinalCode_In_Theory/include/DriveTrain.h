#pragma once

#include "Enums.h"
#include "joystick_config.h"
#include "vex.h"
#include <cmath>

class DriveTrain
{
  public:

  DriveTrain(int topleftMotorport, 
             int toprightMotorport, 
             int bottomleftMotorport, 
             int bottomrightMotorport,
             vex::controller *controller_p);

  void arcadeDrive(int32_t forward, int32_t turn);

  void RealDrive(int32_t left, int32_t right);

  void update(DriveTrain_State state);
  void updateSystemState(System_State state);
  int32_t getLeftSide();
  int32_t getRightSide();

private:
  V5_DeviceT topleftMotor;
  V5_DeviceT toprightMotor;
  V5_DeviceT bottomleftMotor;
  V5_DeviceT bottomrightMotor;
  vex::controller *controller_ptr;
  double topleftmotor_base;
  double toprightmotor_base;
  

};
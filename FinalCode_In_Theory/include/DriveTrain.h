#pragma once

#include "AutoDrive.h"
#include "Enums.h"
#include "joystick_config.h"
#include "vex.h"
#include <cmath>

class DriveTrain
{
  public:

  static constexpr double TICKS_PER_IN = 63.88;

  DriveTrain(int topleftMotorport, 
             int toprightMotorport, 
             int bottomleftMotorport, 
             int bottomrightMotorport,
             vex::controller *controller_p);

  void arcadeDrive(int32_t forward, int32_t turn);

  void RealDrive(int32_t left, int32_t right);

  void update(DriveTrain_State state);
  void updateSystemState(System_State state);
  void updateAuto(Auto_State state);

  int32_t getLeftEncoder();

  int32_t getRightEncoder();

  AutoDrive &getAutoDrive();

  void setPower(int32_t left, int32_t right);

private:
  V5_DeviceT topleftMotor;
  V5_DeviceT toprightMotor;
  V5_DeviceT bottomleftMotor;
  V5_DeviceT bottomrightMotor;
  vex::controller *controller_ptr;
  AutoDrive auto_drive;

  static constexpr double POS_P = 8;
  static constexpr double POS_I = 0;
  static constexpr double POS_D = 0;

  static constexpr double VEL_P = 5;
  static constexpr double VEL_I = 0.4;
  static constexpr double VEL_D = 0;
};
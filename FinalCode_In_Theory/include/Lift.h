#pragma once

#include <cmath>
#include "Enums.h"
#include "Ports.h"
#include "PID.h"
#include "vex.h"

class Lift
{
public:
  Lift(int liftmotorport, 
       int liftmotorport1, 
       vex::triport::port *leftlimitswitchport,
       vex::triport::port *rightimitswitchport,
       vex::brain *brain_p);

  void movePID();

  void moveConst(int32_t speed_left, int32_t speed_right);

  void movebyJoy(int32_t vel);

  void zeroEncoder();

  void update(System_State state, bool go);

  bool getLimitSwitch();

  uint32_t getLeftLiftRotation();
  uint32_t getRightLiftRotation(); 

  void setPIDBounds(int32_t min_power, int32_t max_power);

  void setTargetPos(int32_t target);

  void stopPID();

  int32_t getLeftSetPosition();
  int32_t getRightSetPosition();
  bool getLeftLimitSwitch();
  bool getRightLimitSwitch();
  bool isZeroed();

public:
  V5_DeviceT lift_motor_left;
  V5_DeviceT lift_motor_right;
  bool left_zeroed;
  bool right_zeroed;
  bool switch_val;
private:
  vex::limit zero_switch_left;
  vex::limit zero_switch_right;
  vex::brain *brain_ptr;
  PID<double> lift_pid_left;
  PID<double> lift_pid_right;
public:
  double lift_left_base;
  double lift_right_base;
private:
  static constexpr double P = 150;
  static constexpr double I = 15;
  static constexpr double D = 3;

  void setMotors(int32_t input, int32_t input1);
};
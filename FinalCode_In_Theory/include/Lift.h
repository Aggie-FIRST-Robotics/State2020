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
       vex::triport::port *limitswitchport,
       vex::brain *brain_p);

  void movePID();

  void moveConst(int32_t speed );

  void movebyJoy(int32_t vel);

  void zeroEncoder();

  void update(System_State state);

  bool getLimitSwitch();

  uint32_t getLiftRotation();

  void setPIDBounds(int32_t min_power, int32_t max_power);

  void setTargetPos(int32_t target);

  void stopPID();

  int32_t getSetPosition();

private:
  V5_DeviceT liftmotor;
  V5_DeviceT liftmotor1;
  vex::limit zero_switch;
  vex::brain *brain_ptr;
  PID<double> lift_pid;

  double liftmotor_base;
  
  static constexpr double P = 100;
  static constexpr double I = 10;
  static constexpr double D = 0;

  void setMotors(int32_t input);
};
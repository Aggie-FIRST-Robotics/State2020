#pragma once

#include <cmath>
#include "Enums.h"
#include "Ports.h"
#include "vex.h"

class Lift
{
public:
  Lift(int liftmotorport, 
       int liftmotorport1, 
       vex::triport::port limitswitchport,
       vex::brain *brain_p);

  bool movePosition(double position);

  void moveConst(int32_t speed );

  void movebyJoy(int32_t vel);

  void zeroEncoder();

  void update(System_State state);

  bool getLimitSwitch();

  uint32_t getLiftRotation();

private:
  V5_DeviceT liftmotor;
  V5_DeviceT liftmotor1;
  vex::limit zero_switch;
  vex::brain *brain_ptr;

  double liftmotor_base;
  
  static constexpr double error_treshold = 3.0;
  static constexpr double P = 0.71;
};
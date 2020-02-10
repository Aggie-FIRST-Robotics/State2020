#pragma once

#include <cmath>
#include "Ports.h"
#include "Enums.h"
#include "vex.h"

class Tray
{
public:
  Tray(int traymotorport, 
       int traymotor1port, 
       int zero_switch_port, 
       int cube_switch_port,
       vex::brain *brain_p);
 
  bool movePosition(double position);

  void moveConst(int32_t vel);

  void movebyJoy(int32_t vel);

  void zeroEncoder();

  bool update(System_State state);

private:
  V5_DeviceT traymotor;
  V5_DeviceT traymotor1;
  vex::triport zero_switch;
  vex::triport cube_switch;
  vex::brain *brain_ptr;

  double traymotor_base;

  static constexpr double ERROR_THRESHOLD = 3.0;
  static constexpr double P = 0.71;

  double getTrayRotation();
};
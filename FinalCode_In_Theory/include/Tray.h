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
       vex::triport::port *zero_switch_port, 
       vex::triport::port *cube_switch_port,
       vex::brain *brain_p);
 
  bool movePosition(double position);

  void moveConst(int32_t vel);

  void movebyJoy(int32_t vel);

  void zeroEncoder();

  void update(System_State state);

  bool getLimitSwitch();

  bool getCubeSwitch();

  int32_t getTrayRotation();
  
private:
  V5_DeviceT traymotor;
  V5_DeviceT traymotor1;
  vex::limit zero_switch;
  vex::limit cube_switch;
  
  vex::brain *brain_ptr;

  int32_t traymotor_base;

  static constexpr double ERROR_THRESHOLD = 3.0;
  static constexpr double P = 0.71;
};
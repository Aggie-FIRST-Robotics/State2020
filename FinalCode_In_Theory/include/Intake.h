#pragma once

#include <cmath>
#include "Enums.h"
#include "Ports.h"
#include "vex.h"
#include "joystick_config.h"

class Intake
{
public:
  bool toggle_on;

  Intake(int intakeport_left1, 
               int intakeport_left2, 
               int intakeport_right1, 
               int intakeport_right2, 
               vex::controller *controller_p);

  void moveConst(int32_t speed);

  void joystickIntake(int32_t power);

  void update(System_State state);
  void updateAuto(Auto_State state);

private:
  bool toggle_pressed;
  V5_DeviceT intakeleft1;
  V5_DeviceT intakeleft2;
  V5_DeviceT intakeright1;
  V5_DeviceT intakeright2;
  vex::controller *controller_ptr;
};
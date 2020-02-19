#pragma once

#include <cmath>
#include "Enums.h"
#include "Ports.h"
#include "vex.h"
#include "joystick_config.h"

class Intake
{
public:
  Intake(int intakeport, 
         int intake1port, 
         int intake2port,
         int intake3port,
         vex::controller *controller_p);

  void moveConst(int32_t speed);

  void joystickIntake(int32_t power);

  void update(System_State state);

private:
  V5_DeviceT intake;
  V5_DeviceT intake1;
  V5_DeviceT intake2;
  V5_DeviceT intake3;
  vex::controller *controller_ptr;
};
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
         vex::controller *controller_p);

  void moveConst(int32_t speed);

  void joystickIntake(int32_t power);

  void update(System_State state);
  void updateAuto(Auto_State state);

private:
  V5_DeviceT intake;
  V5_DeviceT intake1;
  vex::controller *controller_ptr;
};
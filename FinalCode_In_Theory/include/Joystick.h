#pragma once

#include "Enums.h"
#include "vex.h"

bool JoystickButtonPressed(vex::controller &controller, Button_Enums port);
int32_t JoystickAxis(vex::controller &controller, Axis_Enums port);
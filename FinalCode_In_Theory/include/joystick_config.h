#pragma once

#include "Joystick.h"

namespace joystick_config{

  static constexpr Button_Enums BASE_BUTTON = Button_Enums::BUTTONB;
  static constexpr Button_Enums TOGGLE_BUTTON = Button_Enums::BUTTONDOWN;
  static constexpr Button_Enums ARM1_BUTTON = Button_Enums::BUTTONA;
  static constexpr Button_Enums ARM2_BUTTON = Button_Enums::BUTTONX;
  static constexpr Button_Enums VERTICAL_BUTTON = Button_Enums::BUTTONY;
  static constexpr Button_Enums INTAKE_BUTTON = Button_Enums::BUTTONL1;
  static constexpr Button_Enums OUTTAKE_BUTTON = Button_Enums::BUTTONL2;
  static constexpr Button_Enums UNFOLD_BUTTON = Button_Enums::BUTTONUP;
  static constexpr Button_Enums TRAY_FLIP_BUTTON = Button_Enums::BUTTONRIGHT;
  static constexpr Button_Enums ARM_FLIP_BUTTON = Button_Enums::BUTTONLEFT;
  static constexpr Button_Enums UP_BUTTON = Button_Enums::BUTTONR1;
  static constexpr Button_Enums DOWN_BUTTON = Button_Enums::BUTTONR2;

  static constexpr Axis_Enums FORWARD_AXIS = Axis_Enums::AXIS3;
  static constexpr Axis_Enums TURN_AXIS = Axis_Enums::AXIS1;
  static constexpr Axis_Enums LEFT_AXIS = Axis_Enums::AXIS3;
  static constexpr Axis_Enums RIGHT_AXIS = Axis_Enums::AXIS2;
};
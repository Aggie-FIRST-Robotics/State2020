#pragma once
#include "vex.h"

namespace Ports
{
  static constexpr int DRIVE_TRAIN_TOP_LEFT_PORT = 11;
  static constexpr int DRIVE_TRAIN_BOTTOM_LEFT_PORT = 12;
  static constexpr int DRIVE_TRAIN_TOP_RIGHT_PORT = 19;
  static constexpr int DRIVE_TRAIN_BOTTOM_RIGHT_PORT = 20;

  static constexpr int INTAKE_PORT_LEFT1 = 1;
  static constexpr int INTAKE_PORT_LEFT2 = 2;
  static constexpr int INTAKE_PORT_RIGHT1 = 9;
  static constexpr int INTAKE_PORT_RIGHT2 = 10;

  static constexpr int TRAY_PORT_0 = 8;
  static constexpr int TRAY_PORT_1 = 3;
  static constexpr int TRAY_CUBE_SWITCH = 3;
  static constexpr int TRAY_ZERO_SWITCH = 1;

  static constexpr int LIFT_PORT_0 = 5;
  static constexpr int LIFT_PORT_1 = 6;
  static constexpr int RIGHT_LIFT_ZERO_SWITCH = 5;
  static constexpr int LEFT_LIFT_ZERO_SWITCH = 6;

  static constexpr double UNFOLD_TIME = 2;
  static constexpr double POSITION_TIME = 2;

  static constexpr double POSITION_CUBE_TIMEOUT = 2.0;
  static constexpr int32_t TRAY_BASE_POSITION = 0;
  static constexpr int32_t TRAY_VERTICAL_POSITION = 1600;

  static constexpr int32_t LIFT_BASE_POSITION = 100;
  static constexpr int32_t  LIFT_BASE_POSITION1 = 400;
  static constexpr int32_t  LIFT_BASE_POSITION2 = 800;
  static constexpr int32_t TRAY_CONSTANT = 10;
  static constexpr int32_t ARM_CONSTANT = 10;
}
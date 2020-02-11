#pragma once

namespace Ports
{
  static constexpr int DRIVE_TRAIN_TOP_LEFT_PORT = 2;
  static constexpr int DRIVE_TRAIN_BOTTOM_LEFT_PORT = 15;
  static constexpr int DRIVE_TRAIN_TOP_RIGHT_PORT = 13;
  static constexpr int DRIVE_TRAIN_BOTTOM_RIGHT_PORT = 14;

  static constexpr int INTAKE_PORT_0 = 2;
  static constexpr int INTAKE_PORT_1 = 10;

  static constexpr int TRAY_PORT_0 = 17;
  static constexpr int TRAY_PORT_1 = 16;
  static constexpr int TRAY_CUBE_SWITCH = 0;
  static constexpr int TRAY_ZERO_SWITCH = 1;

  static constexpr int LIFT_PORT_0 = 17;
  static constexpr int LIFT_PORT_1 = 16;
  static constexpr int LIFT_ZERO_SWITCH = 2;

  static constexpr double UNFOLD_TIME = 2;
  static constexpr double POSITION_TIME = 2;

  static constexpr double POSITION_CUBE_TIMEOUT = 2.0;
  static constexpr double TRAY_BASE_POSITION = 1.0;
  static constexpr double TRAY_VERTICAL_POSITION = 100.0;
  static constexpr double TRAY_VERTICAL_POSITION_THRESH = 5.0;

  static constexpr double LIFT_BASE_POSITION = 1.0;
  static constexpr double  LIFT_BASE_POSITION1 = -300.0;
  static constexpr double  LIFT_BASE_POSITION2 = -450.0;
}
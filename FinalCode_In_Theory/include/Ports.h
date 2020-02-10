#pragma once

namespace Ports
{
  constexpr int DRIVE_TRAIN_TOP_LEFT_PORT =2;
  constexpr int DRIVE_TRAIN_BOTTOM_LEFT_PORT =15;
  constexpr int DRIVE_TRAIN_TOP_RIGHT_PORT =13;
  constexpr int DRIVE_TRAIN_BOTTOM_RIGHT_PORT =14;

  constexpr int INTAKE_PORT_0 =2;
  constexpr int INTAKE_PORT_1 =10;

  constexpr int TRAY_PORT_0 =17;
  constexpr int TRAY_PORT_1 =16;
  constexpr int TRAY_CUBE_SWITCH = 0;
  constexpr int TRAY_ZERO_SWITCH = 1;

  constexpr int LIFT_PORT_0 =17;
  constexpr int LIFT_PORT_1 =16;
  constexpr int LIFT_ZERO_SWITCH = 2;

  constexpr double UNFOLD_OFFSET = 2;

  constexpr double POSITION_CUBE_TIMEOUT = 2;
  constexpr double TRAY_BASE_POSITION = 1;
  constexpr double TRAY_VERTICAL_POSITION = 100;

  constexpr double LIFT_BASE_POSITION = 1.0;
  constexpr double  LIFT_BASE_POSITION1= -300.0;
  constexpr double  LIFT_BASE_POSITION2= -450.0;
}
#pragma once

#include <cmath>
#include "Ports.h"
#include "Enums.h"
#include "PID.h"
#include "vex.h"

class Tray
{
public:
  Tray(int traymotorport, 
      int traymotor1port, 
      vex::triport::port *zero_switch_port, 
      vex::triport::port *cube_switch_port,
      vex::brain *brain_p);
 
  void movePID();

  void moveConst(int32_t vel);

  void movebyJoy(int32_t vel);

  void zeroEncoder();

  void update(System_State state);
  void updateAuto(Auto_State state);

  bool getLimitSwitch();

  bool getCubeSwitch();

  int32_t getTrayRotation();

  void setPIDBounds(int32_t min_power, int32_t max_power);

  void setTargetPos(int32_t target);

  void stopPID();

  int32_t getSetPosition();
private:
  V5_DeviceT traymotor;
  V5_DeviceT traymotor1;
  vex::limit zero_switch;
  vex::limit cube_switch;
  vex::brain *brain_ptr;
  PID<double> tray_pid;

  double traymotor_base;

  static constexpr double P = 100;
  static constexpr double I = 10;
  static constexpr double D = 0;
  

  void setMotors(int32_t input);
};
#pragma once

#include <string>

enum DriveTrain_State{DRIVE, DRIVE_BACK_STATE, OFF}; 
enum System_State{UNFOLD, UNFOLD_ARM_ZERO, TRAY_ZERO, BASE, ARM1, ARM2, ARM_ZERO, POSITION_CUBES, TRAY_VERTICAL};
enum Button_Enums{BUTTONA, BUTTONB, BUTTONY, BUTTONX, BUTTONL1, BUTTONL2, BUTTONR1, BUTTONR2, BUTTONUP, BUTTONRIGHT, BUTTONLEFT, BUTTONDOWN};
enum Axis_Enums{AXIS1, AXIS2, AXIS3, AXIS4};

std::string drive_train_state_to_string(DriveTrain_State state);
std::string system_state_to_string(System_State state);
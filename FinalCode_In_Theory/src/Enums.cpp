#include "Enums.h"

std::string drive_train_state_to_string(DriveTrain_State state){
  switch(state){
    case DRIVE:
      return "DRIVE";
    case DRIVE_BACK_STATE:
      return "DRIVE_BACK_STATE";
    case OFF:
      return "OFF";
    default:
      return "Unkown drive state";
  }
}

std::string system_state_to_string(System_State state){
  switch(state){
    case UNFOLD:
      return std::string{"UNFOLD"};
    case UNFOLD_ARM_ZERO:
      return std::string{"UNFOLD_ARM_ZERO"};
    case TRAY_ZERO:
      return std::string{"TRAY_ZERO"};
    case BASE_ARM:
      return std::string{"BASE ARM"};
    case BASE_TRAY:
      return std::string{"BASE TRAY"};
    case ARM1:
      return std::string{"ARM1"};
    case ARM2:
      return std::string{"ARM2"};
    case ARM_ZERO:
      return std::string{"ARM_ZERO"};
    case POSITION_CUBES:
      return std::string{"POSITION_CUBES"};
    case TRAY_VERTICAL:
      return std::string{"TRAY_VERTICAL"};
    default:
      return std::string{"Unknown system state"};
  }
}
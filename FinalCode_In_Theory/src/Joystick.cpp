#include "Joystick.h"

bool JoystickButtonPressed(vex::controller &controller, Button_Enums port)
{
  switch(port)
  {
    case BUTTONA:
      return controller.ButtonA.pressing();
      break;
    case BUTTONB:
      return controller.ButtonB.pressing();
      break;
    case BUTTONY:
      return controller.ButtonY.pressing();
      break;
    case BUTTONX:
      return controller.ButtonX.pressing();
      break;
    case BUTTONL1:
      return controller.ButtonL1.pressing();
      break;
    case BUTTONL2:
      return controller.ButtonL2.pressing();
      break;
    case BUTTONR1:
      return controller.ButtonR1.pressing();
      break;
    case BUTTONR2:
      return controller.ButtonR2.pressing();
      break;
    case BUTTONUP:
      return controller.ButtonUp.pressing();
      break;
    case BUTTONRIGHT:
      return controller.ButtonRight.pressing();
      break;
    case BUTTONLEFT:
      return controller.ButtonLeft.pressing();
      break;
    case BUTTONDOWN:
      return controller.ButtonDown.pressing();
      break;
  }
  return false;

}


  int32_t JoystickAxis(vex::controller &controller, Axis_Enums port)
  {
    switch(port){
      case AXIS1:
      return controller.Axis1.value();
      case AXIS2:
      return controller.Axis2.value();
      case AXIS3:
      return controller.Axis3.value();
      case AXIS4:
      return controller.Axis4.value();

    }
  return 0;
  }



/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       aamhishrao                                                */
/*    Created:      Sun Feb 02 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "DriveTrain.h"
#include "Enums.h"
#include "Intake.h"
#include "Tray.h"
#include "Lift.h"
#include "Ports.h"
#include <functional>

vex::controller cont(primary);
vex::triport tri(PORT22);

DriveTrain drive(Ports::DRIVE_TRAIN_TOP_LEFT_PORT, 
                 Ports::DRIVE_TRAIN_TOP_RIGHT_PORT, 
                 Ports::DRIVE_TRAIN_TOP_RIGHT_PORT, 
                 Ports::DRIVE_TRAIN_BOTTOM_RIGHT_PORT,
                 &cont);

Intake intake(Ports::INTAKE_PORT_0, 
              Ports::INTAKE_PORT_1,
              &cont);

Lift lift(Ports::LIFT_PORT_0, 
          Ports::LIFT_PORT_1, 
          Ports::LIFT_ZERO_SWITCH,
          &Brain);

Tray tray(Ports::TRAY_PORT_0, 
          Ports::TRAY_PORT_1, 
          &(tri.B), 
          &(tri.A),
          &Brain);

double stored_time;
bool stored_time_iswritable;
vex::timer timer_;

DriveTrain_State currentDriveTrainState = DriveTrain_State::DRIVE;
System_State currentSystemState = System_State::UNFOLD;

int main()
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  timer_.reset();

  /*while(true)
  {

    drive.update(currentDriveTrainState);
    intake.update(currentSystemState);
    lift.update(currentSystemState);
    tray.update(currentSystemState);

    switch(currentDriveTrainState)
    {
      case DRIVE:
        break;

      case OFF:
        break;
    }

    switch(currentSystemState)
    {
      case UNFOLD:
        if(timer_.time(seconds) > Ports::UNFOLD_TIME)
        {
          currentSystemState = UNFOLD_ARM_ZERO;
        }
        
        break;

      case UNFOLD_ARM_ZERO:
        if(lift.getLimitSwitch())
        {
          lift.zeroEncoder();
          currentSystemState = TRAY_ZERO;
        }
        break;

      case ARM_ZERO:
        if(lift.getLimitSwitch())
        {
          lift.zeroEncoder();
          currentSystemState = BASE;
        }
        break;

      case TRAY_ZERO:

        if(tray.getLimitSwitch())
        {
          tray.zeroEncoder();
          currentSystemState = BASE;
        }
       break;

      case BASE:

        if (JoystickButtonPressed(cont, joystick_config::ARM1_BUTTON))
        {
            currentSystemState = ARM1;
        }
        else if (JoystickButtonPressed(cont, joystick_config::ARM2_BUTTON))
        {
            currentSystemState = ARM2;
        }
        else if (JoystickButtonPressed(cont, joystick_config::VERTICAL_BUTTON))
        {
            timer_.reset();
            currentSystemState = TRAY_VERTICAL;
        }
        else if (JoystickButtonPressed(cont, joystick_config::UNFOLD_BUTTON))
        {
            timer_.reset();
            currentSystemState = UNFOLD;
        }
        
        break;

      case ARM1:

        if (JoystickButtonPressed(cont, joystick_config::ARM2_BUTTON))
        {
            currentSystemState = ARM2;
        }
        else if (JoystickButtonPressed(cont, joystick_config::BASE_BUTTON))
        {
            currentSystemState = ARM_ZERO;
        }

        break;
      
      case ARM2:
        
        if (JoystickButtonPressed(cont, joystick_config::ARM1_BUTTON))
        {
            currentSystemState = ARM1;
        }
        else if (JoystickButtonPressed(cont, joystick_config::BASE_BUTTON))
        {
            currentSystemState = ARM_ZERO;
        }
          
        break;


      case POSITION_CUBES:
        if(timer_.time(seconds) > Ports::POSITION_TIME)
        {
          currentSystemState = TRAY_ZERO;
        }
        else if(JoystickButtonPressed(cont, joystick_config::BASE_BUTTON))
        {
          currentSystemState = TRAY_ZERO;
        }
        else if(tray.getCubeSwitch())
        {
          currentSystemState = TRAY_VERTICAL;
        }

        break;

      case TRAY_VERTICAL:
        if(JoystickButtonPressed(cont, joystick_config::BASE_BUTTON))
        {
          currentSystemState = TRAY_ZERO;
        }
        break;

    }
  }

  */

  while(true){
    lift.movebyJoy(JoystickAxis(cont, AXIS1));
    tray.movebyJoy(JoystickAxis(cont, AXIS3));

    Brain.Screen.clearLine(0,vex::color::black);
    Brain.Screen.clearLine(1,vex::color::black);
    Brain.Screen.clearLine(2,vex::color::black);
    Brain.Screen.clearLine(3,vex::color::black);
    Brain.Screen.clearLine(4,vex::color::black);
  
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print("Tray Cube Switch: %d, Tray Limit Switch: %d",tray.getCubeSwitch() , tray.getLimitSwitch());

    Brain.Screen.setCursor(2,1);
    Brain.Screen.print("Tray Arm Rotation; %d", tray.getTrayRotation());

    Brain.Screen.setCursor(3,1);
    Brain.Screen.print("Lift Limit Switch: %d", lift.getLimitSwitch());

    Brain.Screen.setCursor(4,1);
    Brain.Screen.print("Lift Arm Rotation: %d", lift.getLiftRotation());
    Brain.Screen.setCursor(5,1);
    Brain.Screen.print(timer_.time(vex::timeUnits::sec));

    if(tray.getLimitSwitch())
        {
          tray.zeroEncoder();
        }
    if(JoystickButtonPressed(cont, joystick_config::ARM1_BUTTON))
        {
          lift.zeroEncoder();
        }
    Brain.Screen.render();




  }



}



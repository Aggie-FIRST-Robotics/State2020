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

vex::brain robot_brain;
vex::controller cont(primary);

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
          &robot_brain);

Tray tray(Ports::TRAY_PORT_0, 
          Ports::TRAY_PORT_1, 
          Ports::TRAY_ZERO_SWITCH, 
          Ports::TRAY_CUBE_SWITCH,
          &robot_brain);

double stored_time;
bool stored_time_iswritable;
vex::timer timer_;

DriveTrain_State currentDriveTrainState = DriveTrain_State::DRIVE;
System_State currentSystemState = System_State::UNFOLD;

int main()
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  while(true)
  {
    switch(currentDriveTrainState)
    {
      case DRIVE:
        drive.update(DriveTrain_State::DRIVE);
        currentDriveTrainState = DriveTrain_State::DRIVE;
        break; 
    }

    switch(currentSystemState)
    {
      case UNFOLD:

        intake.update(System_State::UNFOLD);
        break;

      case UNFOLD_ARM_ZERO:
        if(intake.update(System_State::UNFOLD_ARM_ZERO))
        {
          currentSystemState = System_State::TRAY_ZERO;
        }
        break;

      case TRAY_ZERO:

        if(lift.update(TRAY_ZERO) && tray.update(TRAY_ZERO))
        currentSystemState = Enums::System_State::BASE;
       break;


      case Enums::System_State::BASE:
        intake.update(Enums::System_State::BASE);
        if (lift.update(Enums::System_State::BASE) && tray.update(Enums::System_State::BASE)){
          ARM1_BUTTON.pressed([]() -> void {
            currentSystemState = Enums::System_State::ARM1;
            });
          ARM2_BUTTON.pressed([]() -> void {
            currentSystemState = Enums::System_State::ARM2;
            });
          VERTICAL_BUTTON.pressed([]() -> void {
            currentSystemState = Enums::System_State::TRAY_VERTICAL;
            });


        }
        
        break;
        case Enums::System_State::ARM1:

        intake.update(Enums::System_State::ARM1);
        lift.update(Enums::System_State::ARM1);
        tray.update(Enums::System_State::ARM1);
        
        ARM2_BUTTON.pressed([]() -> void {
            currentSystemState = Enums::System_State::ARM2;
            });
        BASE_BUTTON.pressed([]() -> void {
            currentSystemState = Enums::System_State::BASE;
            });
          

        break;
      
        case Enums::System_State::ARM2:

        intake.update(Enums::System_State::ARM2);
        lift.update(Enums::System_State::ARM2);
        tray.update(Enums::System_State::ARM2);
        
        ARM1_BUTTON.pressed([]() -> void {
            currentSystemState = Enums::System_State::ARM1;
            });
        BASE_BUTTON.pressed([]() -> void {
            currentSystemState = Enums::System_State::BASE;
            });
          

        break;


        case Enums::System_State::POSITION_CUBES:
        
        if(stored_time_iswritable){
          stored_time = timer_.time(vex::timeUnits::sec) + Ports::POSITION_CUBE_TIMEOUT;
          stored_time_iswritable = false;
        }
        else{
          if(timer_.time(vex::timeUnits::sec) < stored_time){
            intake.update(Enums::System_State::TRAY_VERTICAL);
            lift.update(Enums::System_State::TRAY_VERTICAL);
            tray.update(Enums::System_State::TRAY_VERTICAL);
          }
          else if(tray.cube_switch.value()){
            currentSystemState = Enums::TRAY_VERTICAL;
        }
          else{

            
            stored_time_iswritable = true;
            currentSystemState = Enums::BASE;
          }
  }
       
       

        break;
        case Enums::System_State::TRAY_VERTICAL:
        intake.update(Enums::System_State::TRAY_VERTICAL);
        lift.update(Enums::System_State::TRAY_VERTICAL);
        tray.update(Enums::System_State::TRAY_VERTICAL);
        BASE_BUTTON.pressed([]() -> void {
            currentSystemState = Enums::System_State::BASE;
            });
        break;    
    }
  }
}



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


using namespace vex;
DriveTrain drive = DriveTrain(Ports::DRIVE_TRAIN_TOP_LEFT_PORT, Ports::DRIVE_TRAIN_TOP_RIGHT_PORT, Ports::DRIVE_TRAIN_TOP_RIGHT_PORT, Ports::DRIVE_TRAIN_BOTTOM_RIGHT_PORT);
Intake intake = Intake(Ports::INTAKE_PORT_0, Ports::INTAKE_PORT_1);
Lift lift = Lift(Ports::LIFT_PORT_0, Ports::LIFT_PORT_1, Ports::LIFT_ZERO_SWITCH);
Tray tray = Tray(Ports::TRAY_PORT_0, Ports::TRAY_PORT_1, Ports::TRAY_ZERO_SWITCH, Ports::TRAY_CUBE_SWITCH);

vex::controller Controller = controller(primary);
vex::controller::button BASE_BUTTON = Controller.ButtonA;
vex::controller::button ARM1_BUTTON = Controller.ButtonB;
vex::controller::button ARM2_BUTTON = Controller.ButtonX;
vex::controller::button VERTICAL_BUTTON = Controller.ButtonY;

double stored_time;
bool stored_time_iswritable;
vex::timer timer_;



Enums::DriveTrain_State currentDriveTrainState = Enums::DriveTrain_State::DRIVE;


Enums::System_State currentSystemState = Enums::System_State::UNFOLD;




int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  while(true){
    switch(currentDriveTrainState){
      case Enums::DriveTrain_State::DRIVE:
        drive.update(Enums::DriveTrain_State::DRIVE);
        currentDriveTrainState = Enums::DriveTrain_State::DRIVE;
        break;

      
    }

    switch(currentSystemState){
      case Enums::System_State::UNFOLD:

        intake.update(Enums::System_State::UNFOLD);
        break;

      case Enums::System_State::UNFOLD_ARM_ZERO:
        if(intake.update(Enums::System_State::UNFOLD_ARM_ZERO))
        currentSystemState = Enums::System_State::TRAY_ZERO;
        break;


      case Enums::System_State::TRAY_ZERO:

        if(lift.update(Enums::System_State::TRAY_ZERO)&&tray.update(Enums::System_State::TRAY_ZERO))
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



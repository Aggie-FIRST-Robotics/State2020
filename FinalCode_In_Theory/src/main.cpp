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
controller Controller1 = controller(primary);


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
          Controller1.ButtonB.pressed([]() -> void {
            currentSystemState = Enums::System_State::ARM1;
            });
          Controller1.ButtonX.pressed([]() -> void {
            currentSystemState = Enums::System_State::ARM2;
            });
          Controller1.ButtonL1.pressed([]() -> void {
            currentSystemState = Enums::System_State::TRAY_VERTICAL;
            });


        }
        
        break;
        case Enums::System_State::ARM1:

        intake.update(Enums::System_State::ARM1);
        lift.update(Enums::System_State::ARM1);
        tray.update(Enums::System_State::ARM1);
        
        Controller1.ButtonX.pressed([]() -> void {
            currentSystemState = Enums::System_State::ARM2;
            });
        Controller1.ButtonA.pressed([]() -> void {
            currentSystemState = Enums::System_State::BASE;
            });
          

        break;
      
        case Enums::System_State::ARM2:

        intake.update(Enums::System_State::ARM2);
        lift.update(Enums::System_State::ARM2);
        tray.update(Enums::System_State::ARM2);
        
        Controller1.ButtonB.pressed([]() -> void {
            currentSystemState = Enums::System_State::ARM1;
            });
        Controller1.ButtonA.pressed([]() -> void {
            currentSystemState = Enums::System_State::BASE;
            });
          

        break;


        case Enums::System_State::POSITION_CUBES:
        intake.update(Enums::System_State::TRAY_VERTICAL);
        lift.update(Enums::System_State::TRAY_VERTICAL);
        tray.update(Enums::System_State::TRAY_VERTICAL);

        if(tray.cube_switch.value()){
            currentSystemState = Enums::TRAY_VERTICAL;
        }
        break;
        case Enums::System_State::TRAY_VERTICAL:
        intake.update(Enums::System_State::TRAY_VERTICAL);
        lift.update(Enums::System_State::TRAY_VERTICAL);
        tray.update(Enums::System_State::TRAY_VERTICAL);
        Controller1.ButtonA.pressed([]() -> void {
            currentSystemState = Enums::System_State::BASE;
            });
        break;
        

      
    }

    




  }

  
}



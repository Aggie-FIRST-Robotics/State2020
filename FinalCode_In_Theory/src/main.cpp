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
#include "AutoDrive.h"
#include "DriveTrain.h"
#include "Enums.h"
#include "Intake.h"
#include "Tray.h"
#include "Lift.h"
#include "Ports.h"

void setDriveState(DriveTrain_State new_state);
void setSystemState(System_State new_state);
void setAutoState(Auto_State new_state);

bool init_drive_state;
bool init_system_state;
bool init_auto_state;
Auto_State currentAutoState;
DriveTrain_State currentDriveTrainState;
System_State currentSystemState;
vex::competition comp;

vex::controller cont(vex::controllerType::primary);
vex::triport tri(PORT22);

DriveTrain drive(Ports::DRIVE_TRAIN_TOP_LEFT_PORT, 
                 Ports::DRIVE_TRAIN_TOP_RIGHT_PORT, 
                 Ports::DRIVE_TRAIN_BOTTOM_LEFT_PORT, 
                 Ports::DRIVE_TRAIN_BOTTOM_RIGHT_PORT,
                 &cont);

Intake intake(Ports::INTAKE_PORT_0, 
              Ports::INTAKE_PORT_1,
              &cont);

Lift lift(Ports::LIFT_PORT_0, 
          Ports::LIFT_PORT_1, 
          &(tri.C),
          &Brain);

Tray tray(Ports::TRAY_PORT_0, 
          Ports::TRAY_PORT_1, 
         &(tri.B), 
          &(tri.A),
          &Brain);

vex::timer timer_;

  const AutoDriveConfig stop(1, 1, 0);
  const AutoDriveConfig s1(36*DriveTrain::TICKS_PER_IN, 36*DriveTrain::TICKS_PER_IN, 30*DriveTrain::TICKS_PER_IN);
  const AutoDriveConfig s2(6*DriveTrain::TICKS_PER_IN, 6*DriveTrain::TICKS_PER_IN, 20*DriveTrain::TICKS_PER_IN);
  const AutoDriveConfig s3(11.5*DriveTrain::TICKS_PER_IN, -11.5*DriveTrain::TICKS_PER_IN, 30*DriveTrain::TICKS_PER_IN);
  const AutoDriveConfig s4(24*DriveTrain::TICKS_PER_IN, 24*DriveTrain::TICKS_PER_IN, 30*DriveTrain::TICKS_PER_IN);
  const AutoDriveConfig s5(-24*DriveTrain::TICKS_PER_IN, -24*DriveTrain::TICKS_PER_IN, 30*DriveTrain::TICKS_PER_IN);
  const AutoDriveConfig s6(-11.5*DriveTrain::TICKS_PER_IN, 11.5*DriveTrain::TICKS_PER_IN, 30*DriveTrain::TICKS_PER_IN);
  const AutoDriveConfig s7(-42*DriveTrain::TICKS_PER_IN, -42*DriveTrain::TICKS_PER_IN, 30*DriveTrain::TICKS_PER_IN);
  const AutoDriveConfig s8(4*DriveTrain::TICKS_PER_IN, 4*DriveTrain::TICKS_PER_IN, 20*DriveTrain::TICKS_PER_IN);
  const AutoDriveConfig s9(-11.5*DriveTrain::TICKS_PER_IN, 11.5*DriveTrain::TICKS_PER_IN, 30*DriveTrain::TICKS_PER_IN);
  const AutoDriveConfig s10(36*DriveTrain::TICKS_PER_IN, 36*DriveTrain::TICKS_PER_IN, 30*DriveTrain::TICKS_PER_IN);

void autonomous(){
  setAutoState(FORWARD);
  
  while(true)
  { 

    switch(currentAutoState)
    {
      case(FORWARD):
        if(init_auto_state)
        {
          drive.getAutoDrive().initDrive(&s1, 
                                         &stop, 
                                         2*DriveTrain::TICKS_PER_IN, 
                                         1*DriveTrain::TICKS_PER_IN);
          init_auto_state = false;
        }

        if(drive.getAutoDrive().complete())
        {
          setAutoState(MORE_FORWARD);
        }

        break;

      case(MORE_FORWARD):
        if(init_auto_state)
        {
          drive.getAutoDrive().initDrive(&s2, 
                                         &stop, 
                                         2*DriveTrain::TICKS_PER_IN, 
                                         1*DriveTrain::TICKS_PER_IN);
          init_auto_state = false;
        }
        
        if(drive.getAutoDrive().complete())
        {
          setAutoState(TURN_ONE);
        }

        break;

      case(TURN_ONE):
        if(init_auto_state)
        {
          drive.getAutoDrive().initDrive(&s3, 
                                         &stop, 
                                         1*DriveTrain::TICKS_PER_IN, 
                                         1*DriveTrain::TICKS_PER_IN);          
          init_auto_state = false;
        }
        
        if(drive.getAutoDrive().complete())
        {
          setAutoState(LEFT);
        }

        break;

      case(LEFT):
        if(init_auto_state)
        {
          drive.getAutoDrive().initDrive(&s4, 
                                         &stop, 
                                         2*DriveTrain::TICKS_PER_IN, 
                                         1*DriveTrain::TICKS_PER_IN);          
          init_auto_state = false;
        }
        
        if(drive.getAutoDrive().complete())
        {
          setAutoState(RIGHT);
        }

        break;

      case(RIGHT):
        if(init_auto_state)
        {
          drive.getAutoDrive().initDrive(&s5, 
                                         &stop, 
                                         2*DriveTrain::TICKS_PER_IN, 
                                         1*DriveTrain::TICKS_PER_IN);          
          init_auto_state = false;
        }
     
        if(drive.getAutoDrive().complete())
        {
          setAutoState(TURN_TWO);
        }

        break;

      case(TURN_TWO):
        if(init_auto_state)
        {
          drive.getAutoDrive().initDrive(&s6, 
                                         &stop, 
                                         1*DriveTrain::TICKS_PER_IN, 
                                         1*DriveTrain::TICKS_PER_IN);          
          init_auto_state = false;
        }
             
        if(drive.getAutoDrive().complete())
        {
          setAutoState(BACK);
        }

        break;

      case(BACK):
        if(init_auto_state)
        {
          drive.getAutoDrive().initDrive(&s7, 
                                         &stop, 
                                         2*DriveTrain::TICKS_PER_IN, 
                                         1*DriveTrain::TICKS_PER_IN);          
          init_auto_state = false;
        }
             
        if(drive.getAutoDrive().complete())
        {
          setAutoState(CLEAR);
        }

        break;

      case(CLEAR):
        if(init_auto_state)
        {
          drive.getAutoDrive().initDrive(&s8, 
                                         &stop, 
                                         1*DriveTrain::TICKS_PER_IN, 
                                         1*DriveTrain::TICKS_PER_IN);          
          init_auto_state = false;
        }

        if(drive.getAutoDrive().complete())
        {
          setAutoState(TURN_THREE);
        }

        break;

      case(TURN_THREE):
        if(init_auto_state)
        {
          drive.getAutoDrive().initDrive(&s9, 
                                         &stop, 
                                         1*DriveTrain::TICKS_PER_IN, 
                                         1*DriveTrain::TICKS_PER_IN);          
          init_auto_state = false;
        }

        if(drive.getAutoDrive().complete())
        {
          setAutoState(TO_STACK);
        }

        break;

      case(TO_STACK):
        if(init_auto_state)
        {
          drive.getAutoDrive().initDrive(&s10, 
                                         &stop, 
                                         2*DriveTrain::TICKS_PER_IN, 
                                         1*DriveTrain::TICKS_PER_IN);          
          init_auto_state = false;
        }

        if(drive.getAutoDrive().complete())
        {
          setAutoState(POSITION_CUBES_AUTO);
        }

        break;

      case(POSITION_CUBES_AUTO):
        if(init_auto_state)
        {

          init_auto_state = false;
        }

        if(tray.getCubeSwitch())
        {
          setAutoState(TRAY_VERTICAL_AUTO);
        }

        break;

      case(TRAY_VERTICAL_AUTO):
        if(init_auto_state)
        {
          tray.zeroEncoder();
          tray.setPIDBounds(-6000, 6000);
          tray.setTargetPos(Ports::TRAY_VERTICAL_POSITION);
          timer_.clear();
          init_auto_state = false;
        }

        if(timer_.time() > 5000)
        {
          setAutoState(OUTTAKE);
        }

        break;

      case(OUTTAKE):
        if(init_auto_state)
        {
          tray.setPIDBounds(-6000, 6000);
          tray.setTargetPos(Ports::TRAY_VERTICAL_POSITION);
          timer_.clear();
          init_auto_state = false;
        }

        if(timer_.time() > 5000)
        {
          setAutoState(STOP_AUTO);
        }

        break;

      case(STOP_AUTO):
        if(init_auto_state)
        {
          tray.setPIDBounds(-6000, 6000);
          tray.setTargetPos(Ports::TRAY_BASE_POSITION);
          timer_.clear();
          init_auto_state = false;
        }

        break;
    }

    drive.updateAuto(currentAutoState);
    intake.updateAuto(currentAutoState);
    tray.updateAuto(currentAutoState);

    this_thread::sleep_for(10);
  }
}

void teleop(){
  setDriveState(DRIVE);
  setSystemState(UNFOLD);

  timer_.clear();

  while(true)
  {
    Brain.Screen.clearScreen();

    drive.update(currentDriveTrainState);
    //drive.updateSystemState(currentSystemState);
    intake.update(currentSystemState);
    lift.update(currentSystemState);
    tray.update(currentSystemState);

    switch(currentDriveTrainState)
    {
      case DRIVE:
        break;

      case DRIVE_BACK_STATE:
        break;

      case OFF:
        break;

    }

    switch(currentSystemState)
    {
      case UNFOLD:
        if(init_system_state)
        {
          lift.stopPID();
          tray.stopPID();
          timer_.clear();
          init_system_state = false;
        }

        if(timer_.time(sec) > Ports::UNFOLD_TIME)
        {
          setSystemState(UNFOLD_ARM_ZERO);
        }
        
        break;

      case UNFOLD_ARM_ZERO:
        if(init_system_state)
        {
          lift.stopPID();
          tray.stopPID();
          init_system_state = false;
        }

        if(lift.getLimitSwitch())
        {
          lift.zeroEncoder();
          setSystemState(TRAY_ZERO);
        }
        break;

      case ARM_ZERO:
        if(init_system_state)
        {
          lift.stopPID();
          tray.setPIDBounds(-6000, 6000);
          tray.setTargetPos(Ports::TRAY_BASE_POSITION);
          init_system_state = false;
        }

        if(lift.getLimitSwitch())
        {
          lift.zeroEncoder();
          setSystemState(BASE);
        }
        break;

      case TRAY_ZERO:
        if(init_system_state)
        {
          lift.setPIDBounds(-8000, 8000);
          lift.setTargetPos(Ports::LIFT_BASE_POSITION);
          tray.stopPID();
          init_system_state = false;
        }

        if(tray.getLimitSwitch())
        {
          tray.zeroEncoder();
          setSystemState(BASE);
        }
       break;

      case BASE:
        if(init_system_state)
        {
          lift.setPIDBounds(-8000, 8000);
          lift.setTargetPos(Ports::LIFT_BASE_POSITION);
          tray.setPIDBounds(-6000, 6000);
          tray.setTargetPos(Ports::TRAY_BASE_POSITION);
          init_system_state = false;
        }

        if (JoystickButtonPressed(cont, joystick_config::ARM1_BUTTON))
        {
          setSystemState(ARM1);
        }
        else if (JoystickButtonPressed(cont, joystick_config::ARM2_BUTTON))
        {
          setSystemState(ARM2);
        }
        else if (JoystickButtonPressed(cont, joystick_config::VERTICAL_BUTTON))
        {
          setSystemState(POSITION_CUBES);
        }
        else if (JoystickButtonPressed(cont, joystick_config::UNFOLD_BUTTON))
        {
          setSystemState(UNFOLD);
        }
        
        break;

      case ARM1:
        if(init_system_state)
        {
          lift.setPIDBounds(-8000, 8000);
          lift.setTargetPos(Ports::LIFT_BASE_POSITION1);
          tray.setPIDBounds(-6000, 6000);
          tray.setTargetPos(Ports::TRAY_BASE_POSITION);
          init_system_state = false;
        }

        if (JoystickButtonPressed(cont, joystick_config::ARM2_BUTTON))
        {
          setSystemState(ARM2);
        }
        else if (JoystickButtonPressed(cont, joystick_config::BASE_BUTTON))
        {
          setSystemState(ARM_ZERO);
        }

        break;
      
      case ARM2:
        if(init_system_state)
        {
          lift.setPIDBounds(-8000, 8000);
          lift.setTargetPos(Ports::LIFT_BASE_POSITION2);
          tray.setPIDBounds(-6000, 6000);
          tray.setTargetPos(Ports::TRAY_BASE_POSITION);
          init_system_state = false;
        }
        
        if (JoystickButtonPressed(cont, joystick_config::ARM1_BUTTON))
        {
          setSystemState(ARM1);
        }
        else if (JoystickButtonPressed(cont, joystick_config::BASE_BUTTON))
        {
          setSystemState(ARM_ZERO);
        }
          
        break;


      case POSITION_CUBES:
        if(init_system_state)
        {
          lift.setPIDBounds(-8000, 8000);
          lift.setTargetPos(Ports::LIFT_BASE_POSITION);
          tray.setPIDBounds(-6000, 6000);
          tray.setTargetPos(Ports::TRAY_BASE_POSITION);
          timer_.clear();
          init_system_state = false;
        }
        
        if(timer_.time(sec) > Ports::POSITION_TIME)
        {
          setSystemState(TRAY_ZERO);
        }
        else if(JoystickButtonPressed(cont, joystick_config::BASE_BUTTON))
        {
          setSystemState(TRAY_ZERO);
        }
        else if(tray.getCubeSwitch())
        {
          setSystemState(TRAY_VERTICAL);
        }

        break;

      case TRAY_VERTICAL:
        if(init_system_state)
        {
          lift.setPIDBounds(-8000, 8000);
          lift.setTargetPos(Ports::LIFT_BASE_POSITION);
          tray.setPIDBounds(-6000, 6000);
          tray.setTargetPos(Ports::TRAY_VERTICAL_POSITION);
          init_system_state = false;
          timer_.clear();
        }
        setDriveState(DRIVE_BACK_STATE);

        if(JoystickButtonPressed(cont, joystick_config::BASE_BUTTON))
        {
          setSystemState(TRAY_ZERO);
          setDriveState(DRIVE);
        }
        break;
    }

    Brain.Screen.printAt(10, 20, true, "Tray switch: %d", tray.getLimitSwitch());
    Brain.Screen.printAt(10, 40, true, "Cube switch: %d", tray.getCubeSwitch());
    Brain.Screen.printAt(10, 60, true, "Lift switch: %d", lift.getLimitSwitch());
    Brain.Screen.printAt(10, 80, true, "Tray pos: %d", tray.getTrayRotation());
    Brain.Screen.printAt(10, 100, true, "Lift pos: %d", lift.getLiftRotation());

    Brain.Screen.render();

    this_thread::sleep_for(10);
  }

}
int main()
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  comp.autonomous(autonomous);
  comp.drivercontrol(teleop);
  
  
}

void setDriveState(DriveTrain_State new_state)
{
  currentDriveTrainState = new_state;
  init_drive_state = true;
}

void setSystemState(System_State new_state)
{
  currentSystemState = new_state;
  init_system_state = true;
}

void setAutoState(Auto_State new_state)
{
  currentAutoState = new_state;
  init_auto_state = true;
}

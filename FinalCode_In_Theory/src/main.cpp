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
#include <iostream>

void setDriveState(DriveTrain_State new_state);
void setSystemState(System_State new_state);

bool init_drive_state;
bool init_system_state;
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
              Ports::INTAKE_PORT_2,
              Ports::INTAKE_PORT_3,
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
  const AutoDriveConfig s1(48*DriveTrain::TICKS_PER_IN, 48*DriveTrain::TICKS_PER_IN, 30*DriveTrain::TICKS_PER_IN);
  const AutoDriveConfig s2(6*DriveTrain::TICKS_PER_IN, 6*DriveTrain::TICKS_PER_IN, 20*DriveTrain::TICKS_PER_IN);
  const AutoDriveConfig s3(11.5*DriveTrain::TICKS_PER_IN, -11.5*DriveTrain::TICKS_PER_IN, 30*DriveTrain::TICKS_PER_IN);
  const AutoDriveConfig s4(24*DriveTrain::TICKS_PER_IN, 24*DriveTrain::TICKS_PER_IN, 30*DriveTrain::TICKS_PER_IN);
  const AutoDriveConfig s5(-24*DriveTrain::TICKS_PER_IN, -24*DriveTrain::TICKS_PER_IN, 30*DriveTrain::TICKS_PER_IN);
  const AutoDriveConfig s6(-11.5*DriveTrain::TICKS_PER_IN, 11.5*DriveTrain::TICKS_PER_IN, 30*DriveTrain::TICKS_PER_IN);

void autonomous(){

  drive.getAutoDrive().initDrive(&s1, &stop, 2*DriveTrain::TICKS_PER_IN, 1*DriveTrain::TICKS_PER_IN);
  while(!drive.getAutoDrive().complete())
  {
    drive.getAutoDrive().update(drive.getLeftEncoder(), drive.getRightEncoder());
    drive.setPower(drive.getAutoDrive().leftPower(), drive.getAutoDrive().rightPower());
    this_thread::sleep_for(10);
  }

  drive.getAutoDrive().initDrive(&s2, &stop, 2*DriveTrain::TICKS_PER_IN, 1*DriveTrain::TICKS_PER_IN);
  while(!drive.getAutoDrive().complete())
  {
    drive.getAutoDrive().update(drive.getLeftEncoder(), drive.getRightEncoder());
    drive.setPower(drive.getAutoDrive().leftPower(), drive.getAutoDrive().rightPower());
    this_thread::sleep_for(10);
  }

  drive.getAutoDrive().initDrive(&s3, &stop, 1*DriveTrain::TICKS_PER_IN, 1*DriveTrain::TICKS_PER_IN);
  while(!drive.getAutoDrive().complete())
  {
    drive.getAutoDrive().update(drive.getLeftEncoder(), drive.getRightEncoder());
    drive.setPower(drive.getAutoDrive().leftPower(), drive.getAutoDrive().rightPower());
    this_thread::sleep_for(10);
  }

  drive.getAutoDrive().initDrive(&s4, &stop, 2*DriveTrain::TICKS_PER_IN, 1*DriveTrain::TICKS_PER_IN);
  while(!drive.getAutoDrive().complete())
  {
    drive.getAutoDrive().update(drive.getLeftEncoder(), drive.getRightEncoder());
    drive.setPower(drive.getAutoDrive().leftPower(), drive.getAutoDrive().rightPower());
    this_thread::sleep_for(10);
  }

  drive.getAutoDrive().initDrive(&s5, &stop, 2*DriveTrain::TICKS_PER_IN, 1*DriveTrain::TICKS_PER_IN);
  while(!drive.getAutoDrive().complete())
  {
    drive.getAutoDrive().update(drive.getLeftEncoder(), drive.getRightEncoder());
    drive.setPower(drive.getAutoDrive().leftPower(), drive.getAutoDrive().rightPower());
    this_thread::sleep_for(10);
  }

  drive.getAutoDrive().initDrive(&s6, &stop, 1*DriveTrain::TICKS_PER_IN, 1*DriveTrain::TICKS_PER_IN);
  while(!drive.getAutoDrive().complete())
  {
    drive.getAutoDrive().update(drive.getLeftEncoder(), drive.getRightEncoder());
    drive.setPower(drive.getAutoDrive().leftPower(), drive.getAutoDrive().rightPower());
    this_thread::sleep_for(10);
  }

  drive.setPower(0, 0);
}

void teleop(){
  setDriveState(DRIVE);
  setSystemState(UNFOLD);

  std::cout << "Cool" << std::endl;

  timer_.clear();

  unsigned int x = 0;

  while(true)
  {
    ++x;
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(10, 20, true, "Tray switch: %d", tray.getLimitSwitch());
    Brain.Screen.printAt(10, 40, true, "Cube switch: %d", tray.getCubeSwitch());
    Brain.Screen.printAt(10, 60, true, "Lift switch: %d", lift.getLimitSwitch());
    Brain.Screen.printAt(10, 80, true, "Tray pos: %d", tray.getTrayRotation());
    Brain.Screen.printAt(10, 100, true, "Lift pos: %d", lift.getLiftRotation());
    Brain.Screen.printAt(10, 120, true, "SystemState: %s", system_state_to_string(currentSystemState).c_str());
    Brain.Screen.printAt(10, 140, true, "DriveState: %s", drive_train_state_to_string(currentDriveTrainState).c_str());
    Brain.Screen.printAt(10, 160, true, "Time: %d", x);
    Brain.Screen.printAt(10, 180, true, "Spot1");
    Brain.Screen.render();

    drive.update(currentDriveTrainState);
    Brain.Screen.printAt(10, 180, true, "Spot4");
    Brain.Screen.render();
    intake.update(currentSystemState);
    Brain.Screen.printAt(10, 180, true, "Spot5");
    Brain.Screen.render();
    lift.update(currentSystemState);
    Brain.Screen.printAt(10, 180, true, "Spot6");
    Brain.Screen.render();
    tray.update(currentSystemState);
    Brain.Screen.printAt(10, 180, true, "Spot7");
    Brain.Screen.render();

    switch(currentDriveTrainState)
    {
      case DRIVE:
        break;

      case DRIVE_BACK_STATE:
        break;

      case OFF:
        break;

    }
    Brain.Screen.printAt(10, 180, true, "Spot2");
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
         setSystemState(UNFOLD_ARM_ZERO);

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
       setSystemState(ARM_ZERO);
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
       setSystemState(BASE);


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
        setSystemState(BASE);
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

    Brain.Screen.printAt(10, 180, true, "Spot3");
    Brain.Screen.render();

    

    Brain.Screen.render();
    std::cout << "Time " << x << std::endl;

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



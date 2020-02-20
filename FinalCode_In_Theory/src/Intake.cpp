#include "Intake.h"

Intake::Intake(int intakeport, 
               int intake1port, 
               int intake2port,
               int intake3port,
               vex::controller *controller_p) : 
  intake(vexDeviceGetByIndex(intakeport - 1)), 
  intake1(vexDeviceGetByIndex(intake1port - 1)),
  intake2(vexDeviceGetByIndex(intake2port - 1)),
  intake3(vexDeviceGetByIndex(intake3port - 1)),
  controller_ptr(controller_p)
{
}

void Intake::moveConst(int32_t speed)
{
  Brain.Screen.printAt(10, 200, true, "Speed: %d", speed);
  vexDeviceMotorVoltageSet(intake, -speed);
  vexDeviceMotorVoltageSet(intake1, speed);
  vexDeviceMotorVoltageSet(intake2, -speed);
  vexDeviceMotorVoltageSet(intake3, speed);
}

void Intake::joystickIntake(int32_t power)
{
  if(JoystickButtonPressed(*controller_ptr, joystick_config::INTAKE_BUTTON))
  {
    moveConst(power);
  }
  else if(JoystickButtonPressed(*controller_ptr, joystick_config::OUTTAKE_BUTTON))
  {
    moveConst(-power);
  }
  else
  {  
    moveConst(0);
  }
}

void Intake::update(System_State state)
{
  if(state == UNFOLD)
  {
    moveConst(-12000);
  }
  else if (state == BASE || 
            state == ARM1 || 
            state == ARM2)
  {
    joystickIntake(12000);
  }
  else if (state == POSITION_CUBES)
  {
    moveConst(-6000);
  }
  else if(state == TRAY_VERTICAL)
  {
    joystickIntake(6000);
  }
}
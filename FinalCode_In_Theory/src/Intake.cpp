#include "Intake.h"

Intake::Intake(int intakeport, 
               int intake1port, 
               vex::controller *controller_p) : 
  intake(vexDeviceGetByIndex(intakeport - 1)), 
  intake1(vexDeviceGetByIndex(intake1port - 1)),
  controller_ptr(controller_p)
{
}

void Intake::moveConst(int32_t speed)
{
  vexDeviceMotorVoltageSet(intake, speed);
  vexDeviceMotorVoltageSet(intake1, -speed);
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

bool Intake::update(System_State state)
{
  if(state == System_State::UNFOLD)
  {
    moveConst(-12000);
    return true;
  }
  else if (state == System_State::BASE || 
            state == System_State::ARM1 || 
            state == System_State::ARM2)
  {
    joystickIntake(12000);
    return true;
  }
  else if(state == System_State::TRAY_VERTICAL)
  {
    joystickIntake(6000);
    return true;
  }
  
  return false;
}
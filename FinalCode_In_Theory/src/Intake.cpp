#include "Intake.h"

Intake::Intake(int intakeport_left1, 
               int intakeport_left2, 
               int intakeport_right1, 
               int intakeport_right2, 
               vex::controller *controller_p) : 
  toggle_on(true), 
  intakeleft1(vexDeviceGetByIndex(intakeport_left1 - 1)), 
  intakeleft2(vexDeviceGetByIndex(intakeport_left2 - 1)),
  intakeright1(vexDeviceGetByIndex(intakeport_right1 - 1)), 
  intakeright2(vexDeviceGetByIndex(intakeport_right2 - 1)),
  controller_ptr(controller_p)
{
}

void Intake::moveConst(int32_t speed)
{
  vexDeviceMotorVoltageSet(intakeleft1, speed);
  vexDeviceMotorVoltageSet(intakeleft2, speed);
  vexDeviceMotorVoltageSet(intakeright1, -speed);
  vexDeviceMotorVoltageSet(intakeright2, -speed);
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
  else if(toggle_on)
  {
    moveConst(6000);
  }
  else{
    moveConst(0);
  }

  
}

void Intake::update(System_State state)
{
  if(state == UNFOLD)
  {
    moveConst(-12000);
  }
  else if (state == BASE_ARM || 
            state == BASE_TRAY || 
            state == ARM1 || 
            state == ARM2)
  {
    joystickIntake(12000);
  }
  else if (state == POSITION_CUBES)
  {
    moveConst(-6000);
  }
  else if (state == BASE_ARM || state == BASE_TRAY) {
  
  }
  else if(state == TRAY_VERTICAL)
  {
    joystickIntake(6000);
  }

  if(!JoystickButtonPressed(*controller_ptr, joystick_config::TOGGLE_BUTTON)){
    toggle_pressed = false;
  }
  if(!toggle_pressed && JoystickButtonPressed(*controller_ptr, joystick_config::TOGGLE_BUTTON)){
    toggle_pressed = true;
    toggle_on = !toggle_on;
  }
}

void Intake::updateAuto(Auto_State state)
{
  if(state == FORWARD ||
     state == MORE_FORWARD ||
     state == TURN_ONE ||
     state == LEFT ||
     state == RIGHT)
  {
    moveConst(12000);
  }
  else if(state == POSITION_CUBES_AUTO)
  {
    moveConst(-9000);
  }
  else if(state == OUTTAKE)
  {
    moveConst(-6000);
  }
  else
  {
    moveConst(0);
  }
}
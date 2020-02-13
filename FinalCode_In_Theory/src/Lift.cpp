#include "Lift.h"

Lift::Lift(int liftmotorport, 
           int liftmotorport1, 
           vex::triport::port limitswitchport,
           vex::brain *brain_p) :    
  liftmotor(vexDeviceGetByIndex(liftmotorport - 1)), 
  liftmotor1(vexDeviceGetByIndex(liftmotorport1 - 1)), 
  zero_switch(limitswitchport),
  brain_ptr(brain_p),
  liftmotor_base(0.0)
{
}

bool Lift::movePosition(double position)
{
  double error = position - getLiftRotation();

  if(std::abs(error)>error_treshold)
  {
    vexDeviceMotorVoltageSet(liftmotor, P*error);
    vexDeviceMotorVoltageSet(liftmotor1, -P*error);
    
    brain_ptr->Screen.clearLine(0,vex::color::black);
    brain_ptr->Screen.clearLine(1,vex::color::black);
    brain_ptr->Screen.clearLine(2,vex::color::black);
    brain_ptr->Screen.setCursor(1,0);
    brain_ptr->Screen.setCursor(2,0);
    brain_ptr->Screen.print("Arm rotation: %f degrees", getLiftRotation());

    return false;
  }

  vexDeviceMotorVoltageSet(liftmotor, 0);
  vexDeviceMotorVoltageSet(liftmotor1, 0);

  return true;
}

void Lift::moveConst(int32_t speed )
{
  vexDeviceMotorVoltageSet(liftmotor, speed);
  vexDeviceMotorVoltageSet(liftmotor1, -speed);
}

void Lift::zeroEncoder()
{
  liftmotor_base = vexDeviceMotorPositionGet(liftmotor);
}

void Lift::movebyJoy(int32_t vel)
{
  vexDeviceMotorVoltageSet(liftmotor, vel);
  vexDeviceMotorVoltageSet(liftmotor1, -vel);
  brain_ptr->Screen.clearLine(0,vex::color::black);
  brain_ptr->Screen.clearLine(1,vex::color::black);
  brain_ptr->Screen.setCursor(1,0);
  brain_ptr->Screen.print("Arm rotation: %f degrees", getLiftRotation());
  brain_ptr->Screen.setCursor(2,0);
//  Brain.Screen.print("Claw rotation: %f degrees",motor_claw.rotation(vex::rotationUnits::deg));
}

void Lift::update(System_State state)
{
  if(state == UNFOLD_ARM_ZERO || state == ARM_ZERO)
  {
    moveConst(-6000);
  }
  else if (state == TRAY_ZERO || 
           state == BASE || 
           state == POSITION_CUBES || 
           state == TRAY_VERTICAL)
  {
    movePosition(Ports::LIFT_BASE_POSITION);
  }
  else if(state == ARM1)
  {
    movePosition(Ports::LIFT_BASE_POSITION1);
  }
  else if(state == ARM2)
  {
    movePosition(Ports::LIFT_BASE_POSITION2);
  }
}

uint32_t Lift::getLiftRotation()
{
  uint32_t time;
  return vexDeviceMotorPositionRawGet(liftmotor, &time) - liftmotor_base;
}

bool Lift::getLimitSwitch()
{
  return zero_switch.value();
}
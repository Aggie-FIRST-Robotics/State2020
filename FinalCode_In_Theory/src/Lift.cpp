#include "Lift.h"

Lift::Lift(int liftmotorport, 
           int liftmotorport1, 
           vex::triport::port *limitswitchport,
           vex::brain *brain_p) :    
  liftmotor(vexDeviceGetByIndex(liftmotorport - 1)), 
  liftmotor1(vexDeviceGetByIndex(liftmotorport1 - 1)), 
  zero_switch(*limitswitchport),
  brain_ptr(brain_p),
  lift_pid(0, P, I, D, -12000, 12000, -12000, 12000),
  liftmotor_base(0.0)
{
}

void Lift::movePID()
{
  setMotors((int32_t) lift_pid.compute(getLiftRotation()));
}

void Lift::moveConst(int32_t speed )
{
  setMotors(speed);
}

void Lift::zeroEncoder()
{
  liftmotor_base = vexDeviceMotorPositionGet(liftmotor);
}

void Lift::movebyJoy(int32_t vel)
{
  setMotors(vel);
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
           state == TRAY_VERTICAL ||
           state == ARM1 ||
           state == ARM2)
  {
    movePID();
  }
  else if(state == UNFOLD)
  {
    moveConst(0);
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

void Lift::setPIDBounds(int32_t min_power, int32_t max_power)
{
  lift_pid.setBounds(min_power, max_power);
  lift_pid.setIBounds(min_power, max_power);
}

void Lift::setMotors(int32_t input)
{
    vexDeviceMotorVoltageSet(liftmotor, input);
    vexDeviceMotorVoltageSet(liftmotor1, -input);  
}

void Lift::setTargetPos(int32_t target)
{
  lift_pid.setTarget(target);
}

void Lift::stopPID()
{
  lift_pid.stop();
}
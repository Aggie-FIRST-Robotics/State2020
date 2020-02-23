#include "Lift.h"

Lift::Lift(int liftmotorport, 
           int liftmotorport1, 
           vex::triport::port *leftlimitswitchport,
           vex::triport::port *rightimitswitchport,
           vex::brain *brain_p) :    
  lift_motor_left(vexDeviceGetByIndex(liftmotorport - 1)), 
  lift_motor_right(vexDeviceGetByIndex(liftmotorport1 - 1)), 
  zero_switch_left(*leftlimitswitchport),
  zero_switch_right(*rightimitswitchport),
  brain_ptr(brain_p),
  lift_pid_left(0, P, I, D, -12000, 12000, -12000, 12000 ),
  lift_pid_right(0, P, I, D, -12000, 12000, -12000, 12000),
  lift_left_base(0.0),
  lift_right_base(0.0),
  left_zeroed(false),
  right_zeroed(false)
{
}

void Lift::movePID()
{
  lift_pid_right.setTarget(getLeftLiftRotation());
  int32_t left_val = lift_pid_left.compute(getLeftLiftRotation());
  int32_t right_val = lift_pid_right.compute(getRightLiftRotation());
  setMotors(&left_val, &right_val);
}

void Lift::moveConst(int32_t* speed_left, int32_t* speed_right)
{
  setMotors(speed_left, speed_right);
}

void Lift::zeroEncoder()
{
  lift_left_base = vexDeviceMotorPositionRawGet(lift_motor_left, nullptr);
  lift_right_base = vexDeviceMotorPositionRawGet(lift_motor_right, nullptr);
}

void Lift::movebyJoy(int32_t vel)
{
  setMotors(&vel, &vel);
  brain_ptr->Screen.clearLine(0,vex::color::black);
  brain_ptr->Screen.clearLine(1,vex::color::black);
  brain_ptr->Screen.setCursor(1,0);
 // brain_ptr->Screen.print("Arm rotation: %f degrees", getLiftRotation());
  brain_ptr->Screen.setCursor(2,0);
//  Brain.Screen.print("Claw rotation: %f degrees",motor_claw.rotation(vex::rotationUnits::deg));
}

void Lift::update(System_State state, bool go)
{
  if(state == UNFOLD_ARM_ZERO || state == ARM_ZERO)
  {
    if(!switch_val){
      switch_val = true;
      left_zeroed = false;
      right_zeroed = false;
    }
    int32_t left_val = 0;
    int32_t right_val = 0;
    if(!left_zeroed){
      if(getLeftLimitSwitch()){
        left_zeroed = true;
        lift_left_base = vexDeviceMotorPositionRawGet(lift_motor_left, nullptr);
        lift_pid_left.setTarget(0);
      }
      else{
        left_val = -6000;
      }
    }
    if(!right_zeroed){
      if(getRightLimitSwitch()){
        right_zeroed = true;
        lift_right_base = vexDeviceMotorPositionRawGet(lift_motor_right, nullptr);
      }
      else{
        right_val = -6000;
      }
    }

    if(left_zeroed){
      left_val = lift_pid_left.compute(getLeftLiftRotation());
    }
    if(right_zeroed){
      right_val = lift_pid_right.compute(getRightLiftRotation());
    }

    moveConst(&left_val, &right_val);
  }
  else if(state == BASE_ARM){
    if(go){
      movePID();
    }
    switch_val = false;
  }
  else if (state == TRAY_ZERO || 
           state == BASE_TRAY ||  
           state == POSITION_CUBES || 
           state == TRAY_VERTICAL ||
           state == ARM1 ||
           state == ARM2){
    movePID();
    switch_val = false;
  }
  else if(state == UNFOLD)
  {
    moveConst(0, 0);
    switch_val = false;
  }
  else{
    switch_val = false;
  }
}

uint32_t Lift::getLeftLiftRotation()
{
  uint32_t time;
  return -(vexDeviceMotorPositionRawGet(lift_motor_left, &time) - lift_left_base);
}
uint32_t Lift::getRightLiftRotation()
{
  uint32_t time;
  return vexDeviceMotorPositionRawGet(lift_motor_right, &time) - lift_right_base;
}


bool Lift::getLeftLimitSwitch()
{
  return zero_switch_left.value();
}
bool Lift::getRightLimitSwitch()
{
  return zero_switch_right.value();
}
bool Lift::getLimitSwitch(){
  return (getRightLimitSwitch()) && (getLeftLimitSwitch());
}

void Lift::setPIDBounds(int32_t min_power, int32_t max_power)
{
  lift_pid_left.setBounds(min_power, max_power);
  lift_pid_right.setIBounds(min_power, max_power);
}

void Lift::setMotors(int32_t* input_left, int32_t* input_right)
{
  if(input_left != nullptr){
    vexDeviceMotorVoltageSet(lift_motor_left, -(*input_left));
  }
  if(input_right != nullptr){
    vexDeviceMotorVoltageSet(lift_motor_right, *input_right);
  } 
}

void Lift::setTargetPos(int32_t target)
{
  lift_pid_left.setTarget(target);
}

void Lift::stopPID()
{
  lift_pid_left.stop();
  lift_pid_right.stop();
}
 int32_t Lift::getLeftSetPosition()
 {
   return lift_pid_left.getTarget();
 }
 int32_t Lift::getRightSetPosition()
 {
   return lift_pid_right.getTarget();
 }

bool Lift::isZeroed(){
  return left_zeroed && right_zeroed;
}
#include <cmath>
#include "Enums.h"
class Lift{

public:
vex::motor liftmotor;
vex::motor liftmotor1;
vex::triport zero_switch;
vex::brain Brain;
const int error_treshold = 3;
const float P = 0.71;
constexpr static double LIFT_BASE_POSITION = 1.0;
constexpr static double  LIFT_BASE_POSITION1= -300.0;
constexpr static double  LIFT_BASE_POSITION2= -450.0;
Lift(int liftmotorport, int liftmotorport1, int limitswitchport): liftmotor(liftmotorport), liftmotor1(liftmotorport1), zero_switch(limitswitchport) {


}

bool movewithP(float position){
  //liftmotor.setPosition(0, vex::degrees);
  double error = position - liftmotor.rotation(vex::rotationUnits::deg);

  if(std::abs(error)>error_treshold){
    error = position - liftmotor.rotation(vex::rotationUnits::deg);
    liftmotor.spin(vex::forward);
    liftmotor1.spin(vex::forward);
    liftmotor.setVelocity(P*error, vex::percent);
    liftmotor1.setVelocity(-1*P*error, vex::percent);
    
    Brain.Screen.clearLine(0,vex::color::black);
    Brain.Screen.clearLine(1,vex::color::black);
    Brain.Screen.clearLine(2,vex::color::black);
    Brain.Screen.setCursor(1,0);
    Brain.Screen.setCursor(2,0);
    Brain.Screen.print("Arm rotation: %f degrees",liftmotor.rotation(vex::rotationUnits::deg));

    
    Brain.Screen.render(); //push data to the LCD all at once to prevent image flickering
    return false;
        
  }
    liftmotor.setVelocity(0, vex::percent);
    liftmotor1.setVelocity(0, vex::percent);
    return true;
  

}
void move(float speed ){
  liftmotor.setVelocity(speed, vex::percent);
  liftmotor1.setVelocity(-1*speed, vex::percent);
}

void movebyJoy(float vel){
  liftmotor.spin(vex::forward);
  liftmotor1.spin(vex::forward);
  liftmotor.setVelocity(vel, vex::percent);
  liftmotor1.setVelocity(vel, vex::percent);
  Brain.Screen.clearLine(0,vex::color::black);
  Brain.Screen.clearLine(1,vex::color::black);
  Brain.Screen.setCursor(1,0);
  Brain.Screen.print("Arm rotation: %f degrees",liftmotor.rotation(vex::rotationUnits::deg));
  Brain.Screen.setCursor(2,0);
//  Brain.Screen.print("Claw rotation: %f degrees",motor_claw.rotation(vex::rotationUnits::deg));
  Brain.Screen.render(); //push data to the LCD all at once to prevent image flickering
}
void zeroEncoder(){
  liftmotor.resetRotation();
  liftmotor1.resetRotation();

}
bool update(Enums::System_State state){
  if(state == Enums::System_State::UNFOLD_ARM_ZERO){
    if(!zero_switch.value()){
          move(-0.5);
        }
        else{
          zeroEncoder();
          return true;
        }

  }
  else if (state == Enums::System_State::TRAY_ZERO || state == Enums::System_State::BASE || state ==Enums::System_State::POSITION_CUBES || state ==Enums::System_State::TRAY_VERTICAL){
    return movewithP(Lift::LIFT_BASE_POSITION);
    
  }
  else if(state == Enums::System_State::ARM1){
    return movewithP(Lift::LIFT_BASE_POSITION1);
  }
  else if(state == Enums::System_State::ARM2){
    return movewithP(LIFT_BASE_POSITION2);
  }
 




}





};
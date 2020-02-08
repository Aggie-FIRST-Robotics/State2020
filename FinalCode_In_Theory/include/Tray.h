#include <cmath>
#include "Ports.h"
#include "Enums.h"
class Tray{
public:
const int ERROR_THRESHOLD = 3;
vex::motor traymotor1;
vex::motor traymotor;
vex::triport zero_switch;
vex::triport cube_switch;
vex::brain Brain;
const float P =0.71;
const double TRAY_BASE_POSITION = 1;
const double TRAY_VERTICAL_POSITION = 100;


Tray(int traymotor, int traymotor1, int zero_switch_port, int cube_switch_port): traymotor(traymotor1), traymotor1(traymotor), zero_switch(zero_switch_port), cube_switch(cube_switch){
  




}
 
bool movewithP(float position){
  double error = position - traymotor.rotation(vex::rotationUnits::deg);
  
  if(std::abs(error)>ERROR_THRESHOLD){
    error = position - traymotor.rotation(vex::rotationUnits::deg);
    traymotor1.spin(vex::forward);
    traymotor.spin(vex::forward);
    traymotor.setVelocity(P*error, vex::percent);
    traymotor1.setVelocity(-1*P*error, vex::percent);
    
  Brain.Screen.clearLine(0,vex::color::black);
  Brain.Screen.clearLine(1,vex::color::black);
  Brain.Screen.clearLine(2,vex::color::black);
  Brain.Screen.setCursor(1,0);
  //  Brain.Screen.print("Position: ",error);

  Brain.Screen.setCursor(2,0);
  Brain.Screen.print("Arm rotation: %f degrees",traymotor.rotation(vex::rotationUnits::deg));

  
  Brain.Screen.render(); //push data to the LCD all at once to prevent image flickering
  return false;  
  }
  return true;
  traymotor.setVelocity(0, vex::percent);
  traymotor1.setVelocity(0, vex::percent);

}
void move(float vel){
  traymotor.setVelocity(vel, vex::percent);
  traymotor1.setVelocity(-1*vel, vex::percent);

}
void movebyJoy(float vel){
 traymotor.spin(vex::forward);
  traymotor1.spin(vex::forward);
  traymotor.setVelocity(-vel, vex::percent);
  traymotor1.setVelocity(vel, vex::percent);
  Brain.Screen.clearLine(0,vex::color::black);
  Brain.Screen.clearLine(1,vex::color::black);
  Brain.Screen.setCursor(1,0);
  Brain.Screen.print("Arm rotation: %f degrees",traymotor1.rotation(vex::rotationUnits::deg));
  Brain.Screen.setCursor(2,0);
  // Brain.Screen.print("Claw rotation: %f degrees",motor_claw.rotation(vex::rotationUnits::deg));
  Brain.Screen.render(); //push data to the LCD all at once to prevent image flickering
}

void zeroEncoder(){
  traymotor.resetRotation();
  traymotor1.resetRotation();

}
bool update(Enums::System_State state){
  if(state == Enums::System_State::TRAY_ZERO){
    if(!zero_switch.value()){
      move(-0.5);
    }
        else{
          zeroEncoder();
          return true;
  }

}
else if (state == Enums::System_State::BASE || state == Enums::System_State::ARM1 || state == Enums::System_State::ARM2 || state ==Enums::System_State::POSITION_CUBES ){
  return movewithP(TRAY_BASE_POSITION);
}
else if (state ==Enums::System_State::TRAY_VERTICAL){
    return movewithP(TRAY_VERTICAL_POSITION);
}
}




};
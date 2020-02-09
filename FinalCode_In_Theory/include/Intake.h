#include <cmath>
#include "Enums.h"
#include "Ports.h"
class Intake{

public:
vex::motor intake;
vex::motor intake1;
vex::controller Controller;
vex::controller::button INTAKE_BUTTON;
vex::controller::button OUTTAKE_BUTTON;

double stored_time;
bool stored_time_iswritable;
vex::timer timer_;
Intake(int intakeport, int intakeport1): intake(intakeport), intake1(intakeport1){

}


void move(float speed){
  intake.spin(vex::forward);
  intake1.spin(vex::forward);
  intake.setVelocity(speed, vex::percent);
  intake1.setVelocity(-1*speed, vex::percent);
}

void movebyJoy(float vel){
    intake.spin(vex::forward);
    intake1.spin(vex::forward);
    intake.setVelocity(vel, vex::percent);
    intake1.setVelocity(-1*vel, vex::percent);
}
void intake_(){
    move(-1);

}
void outtake_(){
   move(1);
}
void notake(){
    move(0);
}
bool update(Enums::System_State state){
  if(state== Enums::System_State::UNFOLD){
    if(stored_time_iswritable){
          stored_time = timer_.time(vex::timeUnits::sec) + Ports::UNFOLD_OFFSET;
          stored_time_iswritable = false;
        }
        else{
          if(timer_.time(vex::timeUnits::sec) < stored_time){
            outtake_();
          }
          else{
            notake();
            stored_time_iswritable = true;
            return true;
          }
  }
}
else if (state == Enums::System_State::BASE || state==Enums::System_State::ARM1 || state ==Enums::System_State::POSITION_CUBES){
  if(INTAKE_BUTTON.pressing()){
    intake_();

  }
  else if(OUTTAKE_BUTTON.pressing()){
    outtake_();
  }
  else{
    notake();
  }
  return true;
  



}

else if(state == Enums::System_State::TRAY_VERTICAL){
  if(OUTTAKE_BUTTON.pressing()){
    move(0.5);

  }
  else if(INTAKE_BUTTON.pressing()){
    move(-0.5);
  }
  else{
    notake();
  }
}

}



};
#include "Enums.h"
class DriveTrain{

  public:
  vex::motor topleftMotor;
  vex::motor bottomleftMotor;
  vex::motor toprightMotor;
  vex::motor bottomrightMotor;
  vex::controller Controller;

  
  DriveTrain(int topleftMotorport, int toprightMotorport, int bottomleftMotorport, int bottomrightMotorport):topleftMotor(topleftMotorport), toprightMotor(toprightMotorport), bottomleftMotor(bottomleftMotorport), bottomrightMotor(bottomrightMotorport){
  

  }
  void arcadeDrive(float left, float right){
    topleftMotor.spin(vex::forward);
    bottomrightMotor.spin(vex::forward);
    bottomleftMotor.spin(vex::forward);
    bottomleftMotor.spin(vex::forward);

      topleftMotor.setVelocity(left+right, vex::percent);
      bottomleftMotor.setVelocity(left+right, vex::percent);
      toprightMotor.setVelocity(left-right, vex::percent);
      bottomrightMotor.setVelocity(left-right, vex::percent);

  }
  void RealDrive(float left, float right){
    topleftMotor.spin(vex::forward);
    bottomrightMotor.spin(vex::forward);
    bottomleftMotor.spin(vex::forward);
    bottomleftMotor.spin(vex::forward);

    topleftMotor.setVelocity(left, vex::percent);
    bottomleftMotor.setVelocity(left, vex::percent);
    toprightMotor.setVelocity(right, vex::percent);
    bottomrightMotor.setVelocity(right, vex::percent);
  }
  bool update(Enums::DriveTrain_State state){
    if(state == Enums::DriveTrain_State::DRIVE){
      arcadeDrive(Controller.Axis4.value(), Controller.Axis1.value());
      return true;

    }
    
    


  }






};
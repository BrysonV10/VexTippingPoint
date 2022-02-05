/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// FrontRight           motor         1               
// FrontLeft            motor         2               
// BackRight            motor         3               
// BackLeft             motor         4               
// Controller1          controller                    
// Tow                  motor         5               
// LeftLift             motor         6               
// RightLift            motor         7               
// ArmBump              bumper        A               
// ClawAir              digital_out   H               
// Ringinator           motor         8               
// TowBump              bumper        G               
// Inertial             inertial      12              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "autonfunctions.h"
#include <cmath>
using namespace vex;

competition Competition;

void pre_auton(void) {
  ClawAir.set(true);
  Inertial.calibrate();
  vexcodeInit();
}
bool waitingForTowBump;
void waitForBump(void){waitingForTowBump = true;}
/* Autonomous Task */

void autonomous(void) {
  waitUntil(Inertial.isCalibrating() == false);
  LeftLift.stop(brakeType::hold);
  RightLift.stop(brakeType::hold);
  Ringinator.stop(brakeType::hold);
  Tow.spin(directionType::rev);
  wait(1, timeUnits::sec);
  startSpinBackward(40);
  waitUntil(TowBump.pressing());
  stopWheels();
  Tow.spin(directionType::fwd, 30, velocityUnits::pct);
  wait(0.5, timeUnits::sec);
  moveForward(0.5, 60);
  int initialInertial = Inertial.yaw();
  while(Inertial.yaw()-initialInertial < 85){
    spinLeft(30);
  }
  stopWheels();
  ASForward(80, 60, 6.7, 0);
  initialInertial = Inertial.yaw();
  while(std::abs(Inertial.yaw()-initialInertial) < 85){
    spinRight(30);
  }
  stopWheels();
  Tow.spin(directionType::rev, 50, velocityUnits::pct);
  wait(0.5, timeUnits::sec);
  initialInertial = Inertial.yaw();
  while(Inertial.yaw()-initialInertial < 80){
    spinRight(30);
  }
  stopWheels();
  moveBackward(0.5, 50);
}



/* User Control Task */
bool toRumble = true;
bool pneumaticCont = false;
void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    Controller1.ButtonY.pressed(waitForBump);
    //Drive
    BackLeft.spin(directionType::fwd, Controller1.Axis3.position(percent), velocityUnits::pct);
    FrontLeft.spin(directionType::fwd, Controller1.Axis3.position(percent), velocityUnits::pct);
    BackRight.spin(directionType::fwd, Controller1.Axis2.position(percent), velocityUnits::pct);
    FrontRight.spin(directionType::fwd, Controller1.Axis2.position(percent), velocityUnits::pct);
    
    // Tow Control
    if(Controller1.ButtonDown.pressing()){
      Tow.spin(directionType::fwd, 50, velocityUnits::pct);
    } else if(Controller1.ButtonUp.pressing()){
      Tow.spin(directionType::rev, 50, velocityUnits::pct);
    } else {
      Tow.stop(brakeType::brake);
    }

    if(waitingForTowBump && TowBump.pressing()){
      Tow.spin(directionType::rev, 40, velocityUnits::pct);
      waitingForTowBump = false;
    } else if(waitingForTowBump && TowBump.pressing() == false){
      Tow.spin(directionType::fwd, 20, velocityUnits::pct);
      
    }
    //Drive Forward Button (A button)
    if(Controller1.ButtonA.pressing()){
      if(toRumble){
        toRumble = false;
      }
      BackLeft.spin(directionType::fwd, 80, velocityUnits::pct);
      FrontLeft.spin(directionType::fwd, 80, velocityUnits::pct);
      BackRight.spin(directionType::fwd, 80, velocityUnits::pct);
      FrontRight.spin(directionType::fwd, 80, velocityUnits::pct);
    } else {
      toRumble = true;
      BackLeft.spin(directionType::fwd, Controller1.Axis3.position(percent), velocityUnits::pct);
      FrontLeft.spin(directionType::fwd, Controller1.Axis3.position(percent), velocityUnits::pct);
      BackRight.spin(directionType::fwd, Controller1.Axis2.position(percent), velocityUnits::pct);
      FrontRight.spin(directionType::fwd, Controller1.Axis2.position(percent), velocityUnits::pct);
    }

    //Lift
    if(Controller1.ButtonR2.pressing()){
      LeftLift.spin(directionType::fwd, 80, velocityUnits::pct);
      RightLift.spin(directionType::fwd, 80, velocityUnits::pct);
    } else if(Controller1.ButtonR1.pressing()){
      LeftLift.spin(directionType::rev, 60, velocityUnits::pct);
      RightLift.spin(directionType::rev, 60, velocityUnits::pct);
    } else {
      RightLift.stop(brakeType::hold);
      LeftLift.stop(brakeType::hold);
    }
    // ClawAir.set(pneumaticCont);
    // Controller1.ButtonL1.pressed(changePneumatic);
    if(Controller1.ButtonL1.pressing() && !pneumaticCont){
      ClawAir.set(true);
      pneumaticCont = true;
    } else if(Controller1.ButtonL2.pressing() && pneumaticCont){
      ClawAir.set(false);
      pneumaticCont = false;
    }
    Ringinator.spin(directionType::fwd, 5, velocityUnits::pct);
    wait(20, msec);
  }
}



int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();

 
  while (true) {
    wait(100, msec);
  }
}

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


/* Autonomous Task */

void autonomous(void) {
  waitUntil(Inertial.isCalibrating() == false);
  Ringinator.stop(brakeType::hold);
  Tow.spin(directionType::rev);
  int startingRotationVal = BackLeft.rotation(rotationUnits::rev);
  int InertialVal = 0;
  wait(0.1, timeUnits::sec);
  while(!TowBump.pressing() && std::abs(BackLeft.rotation(rotationUnits::rev)-startingRotationVal) < 5){
    InertialVal = Inertial.yaw();
    //Inertial Auto Straightener
    if(std::abs(BackLeft.rotation(rotationUnits::rev)-startingRotationVal) < 3){
      //go fast before 3.75 rotations
      if(InertialVal < -1){
      BackLeft.spin(directionType::rev, 90, velocityUnits::pct);
      FrontLeft.spin(directionType::rev, 90, velocityUnits::pct);
      BackRight.spin(directionType::rev, 70, velocityUnits::pct);
      FrontRight.spin(directionType::rev, 70, velocityUnits::pct);
    } else if(InertialVal > 1){
      BackLeft.spin(directionType::rev, 70, velocityUnits::pct);
      FrontLeft.spin(directionType::rev, 70, velocityUnits::pct);
      BackRight.spin(directionType::rev, 90, velocityUnits::pct);
      FrontRight.spin(directionType::rev, 90, velocityUnits::pct);
    } else {
      BackLeft.spin(directionType::rev, 90, velocityUnits::pct);
      FrontLeft.spin(directionType::rev, 90, velocityUnits::pct);
      BackRight.spin(directionType::rev, 90, velocityUnits::pct);
      FrontRight.spin(directionType::rev, 90, velocityUnits::pct);
    }
    } else {
      //slow down
      if(InertialVal < 1){
        BackLeft.spin(directionType::rev, 40, velocityUnits::pct);
        FrontLeft.spin(directionType::rev, 40, velocityUnits::pct);
        BackRight.spin(directionType::rev, 38, velocityUnits::pct);
        FrontRight.spin(directionType::rev, 38, velocityUnits::pct);
      } else if(InertialVal > 1){
        BackLeft.spin(directionType::rev, 38, velocityUnits::pct);
        FrontLeft.spin(directionType::rev, 38, velocityUnits::pct);
        BackRight.spin(directionType::rev, 40, velocityUnits::pct);
        FrontRight.spin(directionType::rev, 40, velocityUnits::pct);
      } else {
        BackLeft.spin(directionType::rev, 40, velocityUnits::pct);
        FrontLeft.spin(directionType::rev, 40, velocityUnits::pct);
        BackRight.spin(directionType::rev, 40, velocityUnits::pct);
        FrontRight.spin(directionType::rev, 40, velocityUnits::pct);
      }
    }
    
    vex::wait(0.04, timeUnits::sec);
  }
  stopWheels();
  Controller1.rumble(rumblePulse);
  int howFar = std::abs(BackLeft.rotation(rotationUnits::rev)-startingRotationVal);
  vex::wait(0.1, timeUnits::sec);
  
  Tow.spin(directionType::fwd, 24, velocityUnits::pct);
  vex::wait(0.4, timeUnits::sec);
  Tow.spin(directionType::fwd, 3, velocityUnits::pct);
  moveForward(howFar, 80);
  Tow.spin(directionType::rev, 70, velocityUnits::pct);
  vex::wait(0.2, timeUnits::sec);
  moveForward(1, 50);
  Tow.stop();
  InertialVal = Inertial.yaw();
  int variance = 0;
  if(InertialVal < 0){
    variance = std::abs(InertialVal);
  }
  while(Inertial.yaw()-InertialVal < 53+variance){
    spinLeft(70);
    wait(0.1, timeUnits::sec);
  }
  stopWheels();
  moveBackward(1, 60);
  wait(1, timeUnits::sec);
  Ringinator.spin(directionType::rev, 80, velocityUnits::pct);
  wait(1, timeUnits::sec);
  Ringinator.stop(brakeType::coast);
  wait(0.5, timeUnits::sec);
  moveForward(0.5, 40);
  Ringinator.spin(directionType::fwd);
  wait(0.4, timeUnits::sec);
  Ringinator.stop();
}



/* User Control Task */
bool toRumble = true;
bool pneumaticCont = false;
void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    Brain.Screen.clearScreen();
    Controller1.Screen.clearLine();
    Controller1.Screen.print(Inertial.pitch());
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
      Tow.spin(directionType::rev, 30, velocityUnits::pct);
    }

    if(Controller1.ButtonRight.pressing()){
      Ringinator.spin(directionType::rev);
    } else if(Controller1.ButtonLeft.pressing()){
      Ringinator.spin(directionType::fwd);
    } else {
      Ringinator.stop();
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
    if(Controller1.ButtonR1.pressing()){
      LeftLift.spin(directionType::fwd, 80, velocityUnits::pct);
      RightLift.spin(directionType::fwd, 80, velocityUnits::pct);
    } else if(Controller1.ButtonR2.pressing() && ArmBump.pressing() == false){
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

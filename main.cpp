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
// Vision               vision        11              
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
  while(!TowBump.pressing() && std::abs(BackLeft.rotation(rotationUnits::rev)-startingRotationVal) < 5.4){
    //Controller1.Screen.clearLine();
    InertialVal = Inertial.yaw();
    //Controller1.Screen.print(InertialVal);
    //Inertial Auto Straightener
    if(std::abs(BackLeft.rotation(rotationUnits::rev)-startingRotationVal) < 3.75){
      //go fast before 3.75 rotations
      if(InertialVal < -1){
      BackLeft.spin(directionType::rev, 80, velocityUnits::pct);
      FrontLeft.spin(directionType::rev, 80, velocityUnits::pct);
      BackRight.spin(directionType::rev, 60, velocityUnits::pct);
      FrontRight.spin(directionType::rev, 60, velocityUnits::pct);
    } else if(InertialVal > 1){
      BackLeft.spin(directionType::rev, 60, velocityUnits::pct);
      FrontLeft.spin(directionType::rev, 60, velocityUnits::pct);
      BackRight.spin(directionType::rev, 80, velocityUnits::pct);
      FrontRight.spin(directionType::rev, 80, velocityUnits::pct);
    } else {
      BackLeft.spin(directionType::rev, 80, velocityUnits::pct);
      FrontLeft.spin(directionType::rev, 80, velocityUnits::pct);
      BackRight.spin(directionType::rev, 80, velocityUnits::pct);
      FrontRight.spin(directionType::rev, 80, velocityUnits::pct);
    }
    } else {
      //slow down
      if(InertialVal < -1){
        BackLeft.spin(directionType::rev, 40, velocityUnits::pct);
        FrontLeft.spin(directionType::rev, 40, velocityUnits::pct);
        BackRight.spin(directionType::rev, 30, velocityUnits::pct);
        FrontRight.spin(directionType::rev, 30, velocityUnits::pct);
      } else if(InertialVal > 1){
        BackLeft.spin(directionType::rev, 30, velocityUnits::pct);
        FrontLeft.spin(directionType::rev, 30, velocityUnits::pct);
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
  vex::wait(0.2, timeUnits::sec);
  
  Tow.spin(directionType::fwd, 23, velocityUnits::pct);
  vex::wait(0.4, timeUnits::sec);
  Tow.spin(directionType::fwd, 2, velocityUnits::pct);
  moveForward(3, 80);
  Tow.spin(directionType::rev, 70, velocityUnits::pct);
  vex::wait(0.2, timeUnits::sec);
  moveForward(1, 80);
  Tow.stop();

  startSpinForward(40);
  vex::wait(1.2, timeUnits::sec);
  stopWheels();
  int initialYaw = Inertial.yaw();
  while(Inertial.yaw()-initialYaw < 30){
    spinLeft(70);
    wait(0.1, timeUnits::sec);
  }
  stopWheels();

  vex::wait(0.45, timeUnits::sec);
  stopWheels();
  
  moveBackward(1.4, 60);
  Ringinator.spin(directionType::rev, 50, velocityUnits::pct);
  vex::wait(0.5, timeUnits::sec);
  Ringinator.stop();
  Ringinator.rotateFor(directionType::fwd, 0.3, rotationUnits::rev);
  moveForward(0.4, 60);
  
  spinLeft(60);
  Ringinator.stop(brakeType::hold);
  vex::wait(0.32, timeUnits::sec);
  stopWheels();
  vex::wait(0.2, timeUnits::sec);
  moveBackward(0.5, 30);
  vex::wait(0.3, timeUnits::sec);
  Tow.spin(directionType::fwd, 50, velocityUnits::pct);
  vex::wait(0.5, timeUnits::sec);
  moveForward(1.5, 40);
  Tow.stop();
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

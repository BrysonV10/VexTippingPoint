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
// LeftLift             motor         5               
// RightLift            motor         7               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

competition Competition;

void pre_auton(void) {
  
  vexcodeInit();
}


/* Autonomous Task */

void autonomous(void) {
  
}


/* User Control Task */

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    BackLeft.spin(directionType::fwd, Controller1.Axis3.position(percent), velocityUnits::pct);
    FrontLeft.spin(directionType::fwd, Controller1.Axis3.position(percent), velocityUnits::pct);
    BackRight.spin(directionType::fwd, Controller1.Axis2.position(percent), velocityUnits::pct);
    FrontRight.spin(directionType::fwd, Controller1.Axis2.position(percent), velocityUnits::pct);
    
    
    if(Controller1.ButtonR1.pressing()){
      LeftLift.spin(directionType::fwd, 80, velocityUnits::pct);
      RightLift.spin(directionType::fwd, 80, velocityUnits::pct);
    } else if(Controller1.ButtonR2.pressing()){
      LeftLift.spin(directionType::rev, 50, velocityUnits::pct);
      RightLift.spin(directionType::rev, 50, velocityUnits::pct);
    } else {
      LeftLift.stop();
      RightLift.stop();
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

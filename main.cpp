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
// ---- END VEXCODE CONFIGURED DEVICES ----

/* 

READ THIS FIRST

Configure the motors in the graphical configuration in VEXCode
 - Add an arm motor into the config on whatever port you want (name it Arm)
 - Add a simple DigitalOut (its under the 3 Wire section), name it ClawPnuematic
 - You should now have both in the comment above that says START VEXCODE CONFIGURED DEVICES
 
 Please copy-paste this code into a NEW BLANK program in VEXcode, make sure each motor is configured properly, and set the program SLOT (the number by the title) to 4
*/




#include "vex.h"

using namespace vex;

competition Competition;

void pre_auton(void) {
  
  vexcodeInit();
}


/* Autonomous Task */

void autonomous(void) {
  
}

bool toRumble = false;
/* User Control Task */

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    //Basic Driving stuff, this shouldn't change...
    BackLeft.spin(directionType::fwd, Controller1.Axis3.position(percent), velocityUnits::pct);
    FrontLeft.spin(directionType::fwd, Controller1.Axis3.position(percent), velocityUnits::pct);
    BackRight.spin(directionType::fwd, Controller1.Axis2.position(percent), velocityUnits::pct);
    FrontRight.spin(directionType::fwd, Controller1.Axis2.position(percent), velocityUnits::pct);
    

    // if the arm is spinning in the wrong direction, reverse the motor in the graphical configuration on the top right
    // if the arm is too fast, change the second number (between 1-100, is a percentage), should say 50 right now. 
    if(Controller1.ButtonR1.pressing()){
        Arm.spin(directionType::fwd, 50, velocityUnits::pct);
    } else if(Controller1.ButtonR2.pressing()){
        Arm.spin(directionType::rev, 50, velocityUnits::pct);
    }
    
    //claw pnuematics
    // if the pnuematic is reversed, change the true and false values below. 
    if(Controller1.ButtonL1.pressing()){
        ClawPnuematic.set(true);
    } else {
        ClawPnuematic.set(false);
    }

    // Drive straight forward on Button Up pressed - should be working
    if(Controller1.ButtonUp.pressing()){
      if(toRumble){
        toRumble = false;
        Controller1.rumble(rumbleShort);
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

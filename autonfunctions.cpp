#include "vex.h"
#include <cmath>
using namespace vex;


void moveForward(float rotations, float speed){
  FrontLeft.startRotateFor(directionType::fwd, rotations, rotationUnits::rev, speed, velocityUnits::pct);
  BackLeft.startRotateFor(directionType::fwd, rotations, rotationUnits::rev, speed, velocityUnits::pct);
  FrontRight.startRotateFor(directionType::fwd, rotations, rotationUnits::rev, speed, velocityUnits::pct);
  BackRight.rotateFor(directionType::fwd, rotations, rotationUnits::rev, speed, velocityUnits::pct);
}

void moveForward(float rotations, float speed, bool blocking){
  FrontLeft.startRotateFor(directionType::fwd, rotations, rotationUnits::rev, speed, velocityUnits::pct);
  BackLeft.startRotateFor(directionType::fwd, rotations, rotationUnits::rev, speed, velocityUnits::pct);
  FrontRight.startRotateFor(directionType::fwd, rotations, rotationUnits::rev, speed, velocityUnits::pct);
  BackRight.startRotateFor(directionType::fwd, rotations, rotationUnits::rev, speed, velocityUnits::pct);
}

void moveBackward(float rotations, float speed){
  FrontLeft.startRotateFor(directionType::rev, rotations, rotationUnits::rev, speed, velocityUnits::pct);
  BackLeft.startRotateFor(directionType::rev, rotations, rotationUnits::rev, speed, velocityUnits::pct);
  FrontRight.startRotateFor(directionType::rev, rotations, rotationUnits::rev, speed, velocityUnits::pct);
  BackRight.rotateFor(directionType::rev, rotations, rotationUnits::rev, speed, velocityUnits::pct);
}
void moveBackward(float rotations, float speed, bool blocking){
  FrontLeft.startRotateFor(directionType::rev, rotations, rotationUnits::rev, speed, velocityUnits::pct);
  BackLeft.startRotateFor(directionType::rev, rotations, rotationUnits::rev, speed, velocityUnits::pct);
  FrontRight.startRotateFor(directionType::rev, rotations, rotationUnits::rev, speed, velocityUnits::pct);
  BackRight.startRotateFor(directionType::rev, rotations, rotationUnits::rev, speed, velocityUnits::pct);
}

void startSpinForward(float speed){
  BackLeft.spin(directionType::fwd, speed, velocityUnits::pct);
  FrontLeft.spin(directionType::fwd, speed, velocityUnits::pct);
  BackRight.spin(directionType::fwd, speed, velocityUnits::pct);
  FrontRight.spin(directionType::fwd, speed, velocityUnits::pct);
}

void startSpinBackward(float speed){
  BackLeft.spin(directionType::rev, speed, velocityUnits::pct);
  FrontLeft.spin(directionType::rev, speed, velocityUnits::pct);
  BackRight.spin(directionType::rev, speed, velocityUnits::pct);
  FrontRight.spin(directionType::rev, speed, velocityUnits::pct);
}

void stopWheels(){
  BackLeft.stop(brakeType::brake);
  FrontLeft.stop(brakeType::brake);
  BackRight.stop(brakeType::brake);
  FrontRight.stop(brakeType::brake);
}

void spinRight(float speed){
  BackRight.spin(directionType::fwd, speed, velocityUnits::pct);
  FrontRight.spin(directionType::fwd, speed, velocityUnits::pct);
  BackLeft.spin(directionType::rev, speed, velocityUnits::pct);
  FrontLeft.spin(directionType::rev, speed, velocityUnits::pct);
}

void spinLeft(float speed){
  BackRight.spin(directionType::rev, speed, velocityUnits::pct);
  FrontRight.spin(directionType::rev, speed, velocityUnits::pct);
  BackLeft.spin(directionType::fwd, speed, velocityUnits::pct);
  FrontLeft.spin(directionType::fwd, speed, velocityUnits::pct);
}
int InertialVal, startingRotationVal;
void ASBackward(float fastspeed, float slowspeed, float totalRotations, float fastRotations){
  startingRotationVal = BackLeft.rotation(rotationUnits::rev);
  while(!TowBump.pressing() && std::abs(BackLeft.rotation(rotationUnits::rev)-startingRotationVal) < totalRotations){
    InertialVal = Inertial.yaw();
    //Inertial Auto Straightener
    if(std::abs(BackLeft.rotation(rotationUnits::rev)-startingRotationVal) < fastRotations){
      //go fast before 3.75 rotations
      if(InertialVal < -1){
      BackLeft.spin(directionType::rev, fastspeed, velocityUnits::pct);
      FrontLeft.spin(directionType::rev, fastspeed, velocityUnits::pct);
      BackRight.spin(directionType::rev, fastspeed-20, velocityUnits::pct);
      FrontRight.spin(directionType::rev, fastspeed-20, velocityUnits::pct);
    } else if(InertialVal > 1){
      BackLeft.spin(directionType::rev, fastspeed-20, velocityUnits::pct);
      FrontLeft.spin(directionType::rev, fastspeed-20, velocityUnits::pct);
      BackRight.spin(directionType::rev, fastspeed, velocityUnits::pct);
      FrontRight.spin(directionType::rev, fastspeed, velocityUnits::pct);
    } else {
      BackLeft.spin(directionType::rev, fastspeed, velocityUnits::pct);
      FrontLeft.spin(directionType::rev, fastspeed, velocityUnits::pct);
      BackRight.spin(directionType::rev, fastspeed, velocityUnits::pct);
      FrontRight.spin(directionType::rev, fastspeed, velocityUnits::pct);
    }
    } else {
      //slow down
      if(InertialVal < -1){
        BackLeft.spin(directionType::rev, slowspeed, velocityUnits::pct);
        FrontLeft.spin(directionType::rev, slowspeed, velocityUnits::pct);
        BackRight.spin(directionType::rev, slowspeed-10, velocityUnits::pct);
        FrontRight.spin(directionType::rev, slowspeed-10, velocityUnits::pct);
      } else if(InertialVal > 1){
        BackLeft.spin(directionType::rev, slowspeed-10, velocityUnits::pct);
        FrontLeft.spin(directionType::rev, slowspeed-10, velocityUnits::pct);
        BackRight.spin(directionType::rev, slowspeed, velocityUnits::pct);
        FrontRight.spin(directionType::rev, slowspeed, velocityUnits::pct);
      } else {
        BackLeft.spin(directionType::rev, slowspeed, velocityUnits::pct);
        FrontLeft.spin(directionType::rev, slowspeed, velocityUnits::pct);
        BackRight.spin(directionType::rev, slowspeed, velocityUnits::pct);
        FrontRight.spin(directionType::rev, slowspeed, velocityUnits::pct);
      }
    }
    
    vex::wait(0.04, timeUnits::sec);
  }
  stopWheels();
}



void ASForward(float fastspeed, float slowspeed, float totalRotations, float fastRotations){
  int initialYaw = Inertial.yaw();
  startingRotationVal = BackLeft.rotation(rotationUnits::rev);
  while(!TowBump.pressing() && std::abs(BackLeft.rotation(rotationUnits::rev)-startingRotationVal) < totalRotations){
    Controller1.Screen.clearLine();
    //Controller1.Screen.print(initialYaw-Inertial.yaw());
    InertialVal = Inertial.yaw();
    //Inertial Auto Straightener
    if(std::abs(BackLeft.rotation(rotationUnits::rev)-startingRotationVal) < fastRotations){
      if(initialYaw-InertialVal > 1){
      BackLeft.spin(directionType::fwd, fastspeed, velocityUnits::pct);
      FrontLeft.spin(directionType::fwd, fastspeed, velocityUnits::pct);
      BackRight.spin(directionType::fwd, fastspeed-20, velocityUnits::pct);
      FrontRight.spin(directionType::fwd, fastspeed-20, velocityUnits::pct);
    } else if(initialYaw-InertialVal < -1){
      BackLeft.spin(directionType::fwd, fastspeed-20, velocityUnits::pct);
      FrontLeft.spin(directionType::fwd, fastspeed-20, velocityUnits::pct);
      BackRight.spin(directionType::fwd, fastspeed, velocityUnits::pct);
      FrontRight.spin(directionType::fwd, fastspeed, velocityUnits::pct);
    } else {
      BackLeft.spin(directionType::fwd, fastspeed, velocityUnits::pct);
      FrontLeft.spin(directionType::fwd, fastspeed, velocityUnits::pct);
      BackRight.spin(directionType::fwd, fastspeed, velocityUnits::pct);
      FrontRight.spin(directionType::fwd, fastspeed, velocityUnits::pct);
    }
    } else {
      //slow down
      if(initialYaw-InertialVal > 1){
        BackLeft.spin(directionType::fwd, slowspeed, velocityUnits::pct);
        FrontLeft.spin(directionType::fwd, slowspeed, velocityUnits::pct);
        BackRight.spin(directionType::fwd, slowspeed-10, velocityUnits::pct);
        FrontRight.spin(directionType::fwd, slowspeed-10, velocityUnits::pct);
      } else if(initialYaw-InertialVal < -1){
        BackLeft.spin(directionType::fwd, slowspeed-10, velocityUnits::pct);
        FrontLeft.spin(directionType::fwd, slowspeed-10, velocityUnits::pct);
        BackRight.spin(directionType::fwd, slowspeed, velocityUnits::pct);
        FrontRight.spin(directionType::fwd, slowspeed, velocityUnits::pct);
      } else {
        BackLeft.spin(directionType::fwd, slowspeed, velocityUnits::pct);
        FrontLeft.spin(directionType::fwd, slowspeed, velocityUnits::pct);
        BackRight.spin(directionType::fwd, slowspeed, velocityUnits::pct);
        FrontRight.spin(directionType::fwd, slowspeed, velocityUnits::pct);
      }
    }
    
    vex::wait(0.04, timeUnits::sec);
  }
  stopWheels();
}

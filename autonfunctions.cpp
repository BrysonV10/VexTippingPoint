#include "vex.h"

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

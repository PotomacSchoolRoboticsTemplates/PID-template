#ifndef deviceDefinitions_H
#define deviceDefinitions_H

#include "main.h"
using namespace okapi;
extern std::shared_ptr<ChassisController> chassis;

extern MotorGroup leftChassis;
extern MotorGroup rightChassis;

extern RotationSensor rightTrackingWheel;
extern RotationSensor leftTrackingWheel;

extern Motor bigLift;
extern Motor conveyor;

extern pros::ADIDigitalOut frontClaw1;
extern pros::ADIDigitalOut frontClaw2;
extern pros::ADIDigitalOut backClaw1;
extern pros::ADIDigitalOut backClaw2;

extern pros::IMU inertial;

extern Controller mainCtrl;
extern ControllerButton bigLiftUpButton;
extern ControllerButton bigLiftDownButton;
extern ControllerButton conveyorOnButton;
extern ControllerButton conveyorForwardToggle;
extern ControllerButton tilterButton;
extern ControllerButton frontClawButton;

void initializeChassis();

#endif
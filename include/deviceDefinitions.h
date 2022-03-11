#ifndef deviceDefinitions_H
#define deviceDefinitions_H

#include "main.h"
using namespace okapi;

extern bool backTilterState;
extern bool frontClawState;

extern bool driveEnd;
extern bool turnRightEnd;
extern bool turnLeftEnd;
extern bool liftEnd;
extern bool conveyorEnd;

extern bool driveRunning;
extern bool turnRightRunning;
extern bool turnLeftRunning;
extern bool liftRunning;
extern bool conveyorRunning;

extern double driveVelocity;
extern double turnRightVelocity;
extern double turnLeftVelocity;
extern double liftVelocity;
extern double conveyorVelocity;

extern const double maxDriveVelocity;
extern const double maxTurnRightVelocity;
extern const double maxTurnLeftVelocity;
extern const double maxLiftVelocity;
extern const double maxConveyorVelocity;

extern double driveDistance, turnRightAngle, turnLeftAngle, liftPosition;

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
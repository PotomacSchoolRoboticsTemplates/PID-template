#include "deviceDefinitions.h"

bool backTilterState = true;
bool frontClawState = true;

bool driveEnd = false;
bool turnRightEnd = false;
bool turnLeftEnd = false;
bool liftEnd = false;
bool conveyorEnd = false;

bool driveRunning = false;
bool turnRightRunning = false;
bool turnLeftRunning = false;
bool liftRunning = false;
bool conveyorRunning = false;

double driveVelocity = 600.0;
double turnRightVelocity = 600.0;
double turnLeftVelocity = 600.0;
double liftVelocity = 100.0;
double conveyorVelocity = 450.0;

const double maxDriveVelocity = 600.0;
const double maxTurnRightVelocity = 600.0;
const double maxTurnLeftVelocity = 600.0;
const double maxLiftVelocity = 100.0;
const double maxConveyorVelocity = 600.0;

double driveDistance, turnRightAngle, turnLeftAngle, liftPosition;

std::shared_ptr<ChassisController> chassis;

Motor leftBack(5, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor leftFront(7, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor leftMiddle(20, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor rightFront(4, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor rightBack(13, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor rightMiddle(3, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);

MotorGroup leftChassis  ({leftFront, leftMiddle, leftBack});
MotorGroup rightChassis ({rightFront, rightMiddle, rightBack});

Motor conveyor (12, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::rotations);

Motor bigLift(11, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);

//not necessary but if you don't have Rotation Sensor change the get right tracking wheel in pid to get motor eg. what is in lift pid
RotationSensor rightTrackingWheel(19, true);
RotationSensor leftTrackingWheel(18, false);

pros::ADIDigitalOut frontClaw1('D',true);
pros::ADIDigitalOut frontClaw2('E', true);
pros::ADIDigitalOut backClaw1('G', true);
pros::ADIDigitalOut backClaw2('H', true);

//inertial sensor is not necessary but you need to make your own odom
pros::IMU inertial(15);

Controller mainCtrl(ControllerId::master);
ControllerButton bigLiftUpButton(ControllerDigital::R1);
ControllerButton bigLiftDownButton(ControllerDigital::R2);
ControllerButton conveyorOnButton(ControllerDigital::up);
ControllerButton conveyorForwardToggle(ControllerDigital::down);
ControllerButton tilterButton(ControllerDigital::L2);
ControllerButton frontClawButton(ControllerDigital::L1);

void initializeChassis(){
    chassis = ChassisControllerBuilder()
        .withMotors
            ({leftBack, leftMiddle, leftFront},
            {rightBack, rightMiddle, rightFront})
        .build();
}
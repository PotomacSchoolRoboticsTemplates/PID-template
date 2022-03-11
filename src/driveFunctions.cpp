#include "driveFunctions.h"

const int loopDelay = 15;
const double trackingWheelCircumference = 2.75 * M_PI;
const double deltaT = loopDelay/1000.0;

double drivekP = 1.0;
double drivekI = 0.0;
double drivekD = 0.0;
double turnRightkP, turnRightkI, turnRightkD;
double turnLeftkP, turnLeftkI, turnLeftkD;
double liftkP, liftkI, liftkD;
double rightSidekP, rightSidekI, rightSidekD;
double leftSidekP, leftSidekI, leftSidekD;

double driveTimeout, rightTurnTimeout, leftTurnTimeout, liftTimeout;

double signum(double num){
    if(num>0){
    return 1;
  }
  else if(num<0){
    return -1;
  }
  else{
    return 0;
  }
}

void maxCurrent(double current){
  rightChassis.setCurrentLimit(current);
  leftChassis.setCurrentLimit(current);
}

double bothBind(double num, double upper, double lower){
  if(num > upper){
    return upper;
  } else if(num < lower){
    return lower;
  } else{
    return num;
  }
}

double maxBind(double num, double upper){
  if(num>upper){
    return upper;
  } else{
    return num;
  }
}
double minBind(double num, double lower){
  if(num < lower){
    return lower;
  } else {
    return num;
  }
}

void move(){
    double maxIntegral = 10000.0;
    double currentDistance, driveTarget, driveError = 1000, driveIntegral, driveDerivative, drivePower, driveRuntime, driveLastError, driveTargetTime;

    bool driveZeroPower = false;
    bool firstRun = true;
    while(true){
      if(driveEnd){
        return;
      }
      if(driveRunning && driveRuntime < driveTimeout){
        driveRuntime += loopDelay;
        if(driveError <= 180){
          driveTargetTime += loopDelay;
        } else{
          driveTargetTime = 0.0;
        }
        if(driveTargetTime >= 100){
          driveRunning = false;
        }
        driveTarget = (driveDistance/trackingWheelCircumference) * 360;
        currentDistance = rightTrackingWheel.get();
        driveError = driveTarget - currentDistance;
        if(firstRun){
          driveLastError = driveError;
          firstRun = false;
        }
        driveIntegral += driveError;
        if(driveError > 1500){
          driveIntegral = 0;
        }
        if(driveError <= 0){
          driveIntegral = 0;
        }
        if(driveIntegral > maxIntegral){
          driveIntegral = maxIntegral;
        }
        driveDerivative = driveError - driveLastError;
        driveLastError = driveError;
        drivePower = drivekP * driveError + drivekI * driveIntegral + drivekD * driveDerivative;
        drivePower = bothBind(drivePower, 12000, -12000);
        leftChassis.moveVoltage(drivePower);
        rightChassis.moveVoltage(drivePower);
        driveZeroPower = true;
      } else {
        if(driveZeroPower){
          leftChassis.moveVoltage(0);
          driveZeroPower = false;
        }
        currentDistance = 0;
        driveTarget = 0;
        driveError = 0;
        driveIntegral = 0;
        driveDerivative = 0;
        driveRuntime = 0;
        driveLastError = 0;
        drivePower = 0;
        firstRun = true;
      }
      pros::delay(15);
    }
}
void moveDistance(double driveTargetDistance, double timeOut){
  double maxIntegral = 10000.0;
  double currentDistance = 0.0, driveDerivative = 0.0, drivePower = 0.0, driveRuntime = 0.0;
  double driveTarget = 0.0, driveError = 1000, driveIntegral = 0.0;
  double driveLastError = 0.0, driveTargetTime = 0.0;

  bool firstRun = true;
  bool isRunning = true;
  while(isRunning && driveRuntime < timeOut){
    driveRuntime += loopDelay;
    if(driveError <= 180){
      driveTargetTime += loopDelay;
    } else {
      driveTargetTime = 0.0;
    }
    if(driveTargetTime >= 100){
      isRunning = false;
    }
    driveTarget = (driveTargetDistance/trackingWheelCircumference) * 360;
    currentDistance = rightTrackingWheel.get();
    driveError = driveTarget - currentDistance;
    if(firstRun){
      driveLastError = driveError;
      firstRun = false;
    }
    driveIntegral += driveError;
    if(driveError <= 0){
      driveIntegral = 0;
    }
    if(driveError > 1500){
      driveIntegral = 0;
    }
    if(driveIntegral > maxIntegral){
      driveIntegral = maxIntegral;
    }
    driveDerivative = driveError - driveLastError;
    driveLastError = driveError;
    drivePower = drivekP * driveError + drivekI * driveIntegral + drivekD * driveDerivative;
    drivePower = bothBind(drivePower, 12000, -12000);
    leftChassis.moveVoltage(drivePower);
    rightChassis.moveVoltage(drivePower);
    pros::delay(loopDelay);
  }
  leftChassis.moveVoltage(0);
  rightChassis.moveVoltage(0);
}
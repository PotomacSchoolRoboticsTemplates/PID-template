#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	bool conveyorOnState = false;
	bool conveyorIsOn = false;
	int conveyorIsForward = 1;
	bool tilterActive = true;
	bool tilterState = false;
	bool frontClawActive = true;
	bool frontClawState = false;
	
	while(true){
		chassis->getModel()->tank(mainCtrl.getAnalog(ControllerAnalog::leftY), mainCtrl.getAnalog(ControllerAnalog::rightY));
		if(bigLiftUpButton.isPressed()){
			bigLift.moveVelocity(100);
		} else if (bigLiftDownButton.isPressed()){
			bigLift.moveVelocity(-100);
		} else {
			bigLift.moveVelocity(0);
			
			bigLift.setBrakeMode(AbstractMotor::brakeMode::hold);
		} 
		if(conveyorOnButton.isPressed() && !conveyorOnState){
			conveyorIsOn = !conveyorIsOn;
		}
		if(conveyorForwardToggle.isPressed()){
			conveyor.moveVelocity(-450);
		} else if (conveyorIsOn){
			conveyor.moveVelocity(450);
		} else {
			conveyor.moveVelocity(0);
		}
		if(tilterButton.isPressed() && !tilterState){
			backClaw1.set_value(!tilterActive);
			backClaw2.set_value(!tilterActive);
			tilterActive = !tilterActive;
		}
		if(frontClawButton.isPressed() && !frontClawState){
			frontClaw1.set_value(!frontClawActive);
			frontClaw2.set_value(!frontClawActive);
			frontClawActive = !frontClawActive;
		}
		conveyorOnState = conveyorOnButton.isPressed();
		tilterState = tilterButton.isPressed();
		frontClawState = frontClawButton.isPressed();
		pros::delay(20);
	}
}

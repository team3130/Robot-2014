#include "JoystickTank.h"
#include "math.h"

JoystickTank::JoystickTank(){
	Requires(chassis);
	precisionMultiplier = 0.6666666666f;
	precisionLevel = 0;
}

// Called just before this Command runs the first time
void JoystickTank::Initialize() {
	chassis->drive->DumbRobot();
}

// Called repeatedly when this Command is scheduled to run
void JoystickTank::Execute() {
	//deadzones
	float leftStick = oi->leftJoystick->GetY();
	float rightStick = oi->rightJoystick->GetY();
	if (fabs(leftStick)<.07f){
		leftStick = 0;
	}
	if (fabs(rightStick)<.07f){
		rightStick = 0;
	}
	
	//precision mode
	int leftPrecision = oi->leftPrecision->Get()?1:0;		//1 if button pressed, 0 otherwise.
	int rightPrecision = oi->rightPrecision->Get()?1:0;		//1 if button pressed, 0 otherwise.
	precisionLevel = leftPrecision+rightPrecision;
	float multiplier = pow(precisionMultiplier, precisionLevel);

	chassis->tankDrive(leftStick*multiplier, rightStick*multiplier);
}

// Make this return true when this Command no longer needs to run execute()
bool JoystickTank::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void JoystickTank::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void JoystickTank::Interrupted() {
}

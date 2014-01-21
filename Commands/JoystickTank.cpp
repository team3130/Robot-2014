#include "JoystickTank.h"
#include "math.h"

JoystickTank::JoystickTank(){
	Requires(chassis);
	precisionMultiplier = 0.6666666666f;
	precisionLevel = 0;
	maxPrecisionLevel = 2;
	SmartDashboard::PutNumber("JoystickTank: Joystick To Speed Multiplier (m/s)",1.f);
}
// Called just before this Command runs the first time
void JoystickTank::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void JoystickTank::Execute() {
	//deadzones
	float leftStick = oi->leftJoystick->GetY();
	float rightStick = oi->leftJoystick->GetY();
	if (fabs(leftStick)<.1f){
		leftStick = 0;
	}
	if (fabs(rightStick)<.1f){
		rightStick = 0;
	}
	//precision mode
	int leftPrecision = oi->leftPrecision->Get()?1:0;		//1 if button pressed, 0 otherwise.
	int rightPrecision = oi->rightPrecision->Get()?1:0;		//1 if button pressed, 0 otherwise.
	precisionLevel = leftPrecision+rightPrecision;
	float multiplier = pow(precisionMultiplier, precisionLevel);

	chassis->tankDrive(joystickToSpeed(leftStick*multiplier),
			joystickToSpeed(rightStick*multiplier));
}
//convert joystick value to a speed (m/s)
float JoystickTank::joystickToSpeed(float in){
	return in * SmartDashboard::GetNumber("JoystickTank: Joystick To Speed Multiplier (m/s)");
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

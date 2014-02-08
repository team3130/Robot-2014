#include "JoystickStraight.h"
#include "math.h"

JoystickStraight::JoystickStraight(){
	Requires(chassis);
}
// Called just before this Command runs the first time
void JoystickStraight::Initialize() {
	chassis->InitEncoders();
	chassis->SmartRobot();
}

// Called repeatedly when this Command is scheduled to run
void JoystickStraight::Execute() {
	double power = oi->rightJoystick->GetY();
	if(fabs(power)<0.07) power=0;
	double turn = oi->leftJoystick->GetX();
	if(fabs(turn)<0.2) turn = 0;
	
	chassis->arcadeDrive(power,turn);
}

// Make this return true when this Command no longer needs to run execute()
bool JoystickStraight::IsFinished() {
	return !oi->straightMode->Get();
}

// Called once after isFinished returns true
void JoystickStraight::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void JoystickStraight::Interrupted() {
	
}

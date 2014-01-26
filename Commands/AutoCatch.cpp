#include "AutoCatch.h"

AutoCatch::AutoCatch(){
	Requires(chassis);
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}
// Called just before this Command runs the first time
void AutoCatch::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void AutoCatch::Execute() {
	int leftPrecision = oi->leftPrecision->Get()?1:0;		//1 if button pressed, 0 otherwise. Google the Question Mark Operator
	int rightPrecision = oi->rightPrecision->Get()?1:0;		//1 if button pressed, 0 otherwise. Google the Question Mark Operator
	//chassis->tankDrive(oi->leftJoystick,oi->rightJoystick,leftPrecision + rightPrecision);
}

// Make this return true when this Command no longer needs to run execute()
bool AutoCatch::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void AutoCatch::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoCatch::Interrupted() {
	
}

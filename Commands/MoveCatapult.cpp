#include "MoveCatapult.h"

MoveCatapult::MoveCatapult() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(chassis);
}

// Called just before this Command runs the first time
void MoveCatapult::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void MoveCatapult::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool MoveCatapult::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void MoveCatapult::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveCatapult::Interrupted() {
	
}

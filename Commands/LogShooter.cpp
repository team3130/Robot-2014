#include "LogShooter.h"

LogShooter::LogShooter() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(shooter);
}

// Called just before this Command runs the first time
void LogShooter::Initialize() {
	log = Logger::GetInstance();
}

// Called repeatedly when this Command is scheduled to run
void LogShooter::Execute() {
	log->update_number("Shooter.Catapult.Position", shooter->getCatapultPosition());
//	log->update_bool("Shooter.LimitSwitch.Value", shooter->limitSwitch->Get());
}

// Make this return true when this Command no longer needs to run execute()
bool LogShooter::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void LogShooter::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LogShooter::Interrupted() {
}

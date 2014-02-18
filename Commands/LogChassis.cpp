#include "LogChassis.h"

LogChassis::LogChassis(const char* name) : CommandBase(name) {
	// Use requires() here to declare subsystem dependencies
	Requires(chassis);
}

// Called just before this Command runs the first time
void LogChassis::Initialize() {
	m_logger = Logger::GetInstance();
}

// Called repeatedly when this Command is scheduled to run
void LogChassis::Execute() {
	m_logger->update_number("Chassis.Gyro.Value", chassis->gyro->GetAngle());
	m_logger->update_bool("Chassis.Drive.IsAlive", chassis->drive->IsAlive());
	m_logger->update_bool("Chassis.Shifter.Position", chassis->shifter->Get());
	m_logger->update_number("Chassis.LeftEncoder.Rate", chassis->leftController->GetRate());
	m_logger->update_number("Chassis.LeftEncoder.Value", chassis->leftController->GetEncoder());
	m_logger->update_number("Chassis.RightEncoder.Rate", chassis->rightController->GetRate());
	m_logger->update_number("Chassis.RightEncoder.Value", chassis->rightController->GetEncoder());


}

// Make this return true when this Command no longer needs to run execute()
bool LogChassis::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void LogChassis::End() {
	m_logger = NULL;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LogChassis::Interrupted() {
}

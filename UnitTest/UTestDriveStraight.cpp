#include "UTestDriveStraight.h"

UTestDriveStraight::UTestDriveStraight() : CommandGroup("UTest Drive Straight") {
	m_command = new DriveStraight("DriveStraight for UTest");
	AddSequential(m_command);
	SmartDashboard::PutData(this);
	SmartDashboard::PutNumber("UTest Straight Distance",12.0);
	SmartDashboard::PutNumber("UTest Straight Tolerance",1.0);
	SmartDashboard::PutNumber("UTest Straight Cooldown",1.5);
}

void UTestDriveStraight::Initialize() {
	// distance is in encoder units, 1 unit = N of pulses in 1 sec at top speed.
	m_command->SetGoal(
			SmartDashboard::GetNumber("UTest Straight Distance"),
			SmartDashboard::GetNumber("UTest Straight Tolerance"),
			SmartDashboard::GetNumber("UTest Straight Cooldown")
		);
}

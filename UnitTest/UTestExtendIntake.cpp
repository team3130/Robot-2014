#include "UTestExtendIntake.h"

UTestExtendIntake::UTestExtendIntake() : CommandGroup("UTest Extend Intake") {
	m_command = new ExtendIntake();
	AddSequential(m_command);
	SmartDashboard::PutData(this);
	SmartDashboard::PutNumber("UTest Extend Intake X", .707);
	SmartDashboard::PutNumber("UTest Extend Intake Y", .707);
	SmartDashboard::PutNumber("UTest Extend Intake Rotation",-90);
}

void UTestExtendIntake::Initialize() {
	// distance is in encoder units, 1 unit = N of pulses in 1 sec at top speed.
	m_command->Execute(
			//SmartDashboard::GetNumber("UTest Extend Intake X"),
			//SmartDashboard::GetNumber("UTest Extend Intake Y"),
			//SmartDashboard::GetNumber("UTest Extend Intake Rotation")
		);
}

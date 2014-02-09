#include "UTestSpinIntake.h"

UTestSpinIntake::UTestSpinIntake() : CommandGroup("UTest Spin Intake") {
	m_command = new SpinIntake();
	AddSequential(m_command);
//	SmartDashboard::PutData(this);
//	SmartDashboard::PutNumber("UTest Spin Intake X", .707);
//	SmartDashboard::PutNumber("UTest Spin Intake Y", .707);
//	SmartDashboard::PutNumber("UTest Spin Intake Rotation",-90);
}

void UTestSpinIntake::Initialize() {
	// distance is in encoder units, 1 unit = N of pulses in 1 sec at top speed.
	m_command->Execute(
			//SmartDashboard::GetNumber("UTest Spin Intake X"),
			//SmartDashboard::GetNumber("UTest Spin Intake Y"),
			//SmartDashboard::GetNumber("UTest Spin Intake Rotation")
		);
}

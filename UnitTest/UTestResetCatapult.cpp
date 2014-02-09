#include "UTestResetCatapult.h"

UTestResetCatapult::UTestResetCatapult() : CommandGroup("UTest Reset Catapult") {
	m_command = new ResetCatapult();
	AddSequential(m_command);
//	SmartDashboard::PutData(this);
//	SmartDashboard::PutNumber("UTest Reset Catapult X", .707);
//	SmartDashboard::PutNumber("UTest Reset Catapult Y", .707);
//	SmartDashboard::PutNumber("UTest Reset Catapult Rotation",-90);
}

void UTestResetCatapult::Initialize() {
	// distance is in encoder units, 1 unit = N of pulses in 1 sec at top speed.
	m_command->Initialize(
			//SmartDashboard::GetNumber("UTest Reset Catapult X"),
			//SmartDashboard::GetNumber("UTest Reset Catapult Y"),
			//SmartDashboard::GetNumber("UTest Reset Catapult Rotation")
		);
}

#include "UTestWindCatapult.h"

UTestWindCatapult::UTestWindCatapult() : CommandGroup("UTest Move Catapult") {
	m_command = new WindCatapult();
	AddSequential(m_command);
//	SmartDashboard::PutData(this);
//	SmartDashboard::PutNumber("UTest Wind Catapult X", .707);
//	SmartDashboard::PutNumber("UTest Wind Catapult Y", .707);
//	SmartDashboard::PutNumber("UTest Wind Catapult Rotation",-90);
}

void UTestWindCatapult::Initialize() {
	// distance is in encoder units, 1 unit = N of pulses in 1 sec at top speed.
	m_command->Initialize(
			//SmartDashboard::GetNumber("UTest Wind Catapult X"),
			//SmartDashboard::GetNumber("UTest Wind Catapult Y"),
			//SmartDashboard::GetNumber("UTest Wind Catapult Rotation")
		);
}

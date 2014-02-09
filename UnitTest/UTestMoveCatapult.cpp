#include "UTestMoveCatapult.h"

UTestMoveCatapult::UTestMoveCatapult() : CommandGroup("UTest Move Catapult") {
	m_command = new MoveCatapult();
	AddSequential(m_command);
	SmartDashboard::PutData(this);
	SmartDashboard::PutNumber("UTest Move Catapult X", .707);
	SmartDashboard::PutNumber("UTest Move Catapult Y", .707);
	SmartDashboard::PutNumber("UTest Move Catapult Rotation",-90);
}

void UTestMoveCatapult::Initialize() {
	// distance is in encoder units, 1 unit = N of pulses in 1 sec at top speed.
	m_command->Execute(
			//SmartDashboard::GetNumber("UTest Move Catapult X"),
			//SmartDashboard::GetNumber("UTest Move Catapult Y"),
			//SmartDashboard::GetNumber("UTest Move Catapult Rotation")
		);
}

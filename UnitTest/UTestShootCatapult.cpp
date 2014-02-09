#include "UTestShootCatapult.h"

UTestShootCatapult::UTestShootCatapult() : CommandGroup("UTest Shoot Catapult") {
	m_command = new ShootCatapult();
	AddSequential(m_command);
//	SmartDashboard::PutData(this);
//	SmartDashboard::PutNumber("UTest Shoot Catapult X", .707);
//	SmartDashboard::PutNumber("UTest Shoot Catapult Y", .707);
//	SmartDashboard::PutNumber("UTest Shoot Catapult Rotation",-90);
}

void UTestShootCatapult::Initialize() {
	// distance is in encoder units, 1 unit = N of pulses in 1 sec at top speed.
	m_command->Execute(
			//SmartDashboard::GetNumber("UTest Shoot Catapult X"),
			//SmartDashboard::GetNumber("UTest Shoot Catapult Y"),
			//SmartDashboard::GetNumber("UTest Shoot Catapult Rotation")
		);
}

#include "UTestChangeCatapultEnd.h"

UTestChangeCatapultEnd::UTestChangeCatapultEnd() : CommandGroup("UTest Change Catapult End") {
	m_command = new ChangeCatapultEnd();
	AddSequential(m_command);
	//SmartDashboard::PutData(this);
	//SmartDashboard::PutNumber("UTest Change Catapult End X", .707);
	//SmartDashboard::PutNumber("UTest Change Catapult End Y", .707);
	//SmartDashboard::PutNumber("UTest Change Catapult End Rotation",-90);
}

void UTestChangeCatapultEnd::Initialize() {
	// distance is in encoder units, 1 unit = N of pulses in 1 sec at top speed.
	m_command->Execute(
			//SmartDashboard::GetNumber("UTest Extend Intake X"),
			//SmartDashboard::GetNumber("UTest Extend Intake Y"),
			//SmartDashboard::GetNumber("UTest Extend Intake Rotation")
		);
}

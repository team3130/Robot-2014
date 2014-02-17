#include "UTestNavigateTo.h"

UTestNavigateTo::UTestNavigateTo() : CommandGroup("UTest Navigate To") {
	m_command = new NavigateTo("UTest NavigateTo");
	AddSequential(m_command);
	SmartDashboard::PutData(this);
	SmartDashboard::PutNumber("UTest Navigate X", .707);
	SmartDashboard::PutNumber("UTest Navigate Y", .707);
	SmartDashboard::PutNumber("UTest Navigate Rotation",-90);
}

void UTestNavigateTo::Initialize() {
	// distance is in encoder units, 1 unit = N of pulses in 1 sec at top speed.
	m_command->SetGoalCartesian(
			SmartDashboard::GetNumber("UTest Navigate X"),
			SmartDashboard::GetNumber("UTest Navigate Y"),
			SmartDashboard::GetNumber("UTest Navigate Rotation")
		);
}

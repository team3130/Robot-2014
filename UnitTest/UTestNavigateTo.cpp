#include "UTestNavigateTo.h"

UTestNavigateTo::UTestNavigateTo() : CommandGroup("UTest Navigate To") {
	m_command = new NavigateTo();
	AddSequential(m_command);
	SmartDashboard::PutData(this);
	SmartDashboard::PutNumber("UTest Navigate Rotation 1",45);
	SmartDashboard::PutNumber("UTest Navigate Distance", .5);
	SmartDashboard::PutNumber("UTest Navigate Rotation 2",-90);
}

void UTestNavigateTo::Initialize() {
	// distance is in encoder units, 1 unit = N of pulses in 1 sec at top speed.
	m_command->SetGoalPolar(
			SmartDashboard::GetNumber("UTest Navigate Rotation 1"),
			SmartDashboard::GetNumber("UTest Navigate Distance"),
			SmartDashboard::GetNumber("UTest Navigate Rotation 2")
		);
}

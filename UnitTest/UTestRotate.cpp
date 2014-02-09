#include "UTestRotate.h"

UTestRotate::UTestRotate() : CommandGroup("UTest Rotate") {
	m_command = new Rotate("UTest Rotate Command");
	AddSequential(m_command);
	SmartDashboard::PutData(this);
	SmartDashboard::PutNumber("UTest Rotate Distance",90.0);
	SmartDashboard::PutNumber("UTest Rotate Tolerance",3.0);
	SmartDashboard::PutNumber("UTest Rotate Cooldown",1.0);
}

void UTestRotate::Initialize() {
	m_command->SetGoal(
			SmartDashboard::GetNumber("UTest Rotate Distance"),
			SmartDashboard::GetNumber("UTest Rotate Tolerance"),
			SmartDashboard::GetNumber("UTest Rotate Cooldown")
		);
}

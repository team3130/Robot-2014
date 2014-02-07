/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Erin Duebner, James Li                                         */
/*-------------------------------------------------------------------------*/

#include "Intake.h"
#include "../Robotmap.h"
#include "../Commands/SpinIntake.h"

Intake::Intake(int intakeChannel, int extendChannel) : Subsystem("Intake") {
	intakeEncoder = new Encoder(C_ENCODER_INTAKE_CHANNEL_1, C_ENCODER_INTAKE_CHANNEL_2);
	intake = new Jaguar(intakeChannel);
	extend = new Solenoid(extendChannel);
}
    
void Intake::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new SpinIntake());
}

void Intake::TakeBall(bool isOn){
	double power = isOn ? 1 : 0;
	intakeEncoder->SetDistancePerPulse(power);
	intake->SetSpeed((float)power);
}

void Intake::ExtendArms(bool extended){
	extend->Set(extended);
}

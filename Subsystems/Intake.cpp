/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Erin Duebner, James Li                                         */
/*-------------------------------------------------------------------------*/

#include "Intake.h"
#include "../Robotmap.h"
#include "../Commands/StopIntake.h"

Intake::Intake(int intakeChannel, int extendChannelA, int extendChannelB) : Subsystem("Intake") {
	intakeEncoder = new Encoder(C_ENCODER_INTAKE_CHANNEL_A, C_ENCODER_INTAKE_CHANNEL_B);
	intake = new Jaguar(intakeChannel);
	extend1 = new Solenoid(extendChannelA);
	extend2 = new Solenoid(extendChannelB);
}

Intake::~Intake(){
	delete intakeEncoder;
	delete intake;
	delete extend1;
	delete extend2;
}

void Intake::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new StopIntake());
}

bool Intake::getExtend1(){
	return extend1->Get();
}

bool Intake::getExtend2(){
	return extend2->Get();
}

bool Intake::getSpin(){
	return intake->Get() != 0;
}

void Intake::setSpin(bool isOn){
	double power = isOn ? 1 : 0;
	intake->SetSpeed((float)power);
}

void Intake::setExtend(bool isExtend){
	extend1->Set(isExtend);
	extend2->Set(isExtend);
}

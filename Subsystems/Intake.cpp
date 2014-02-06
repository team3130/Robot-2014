/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li                                                       */
/*-------------------------------------------------------------------------*/

#include "Intake.h"
#include "../Robotmap.h"

Intake::Intake(int intakeChannel) : Subsystem("Intake") {
	intakeEncoder = new Encoder(C_ENCODER_INTAKE_CHANNEL_1, C_ENCODER_INTAKE_CHANNEL_2);
	intake = new Jaguar(intakeChannel);
}
    
void Intake::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}


// Put methods for controlling this subsystem
// here. Call these from Commands.


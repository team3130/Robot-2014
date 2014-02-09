/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li                                                       */
/*-------------------------------------------------------------------------*/

#include "SpinIntake.h"

SpinIntake::SpinIntake() {
	Requires(intake);
}

// Called just before this Command runs the first time
void SpinIntake::Initialize() {
	intake->intakeEncoder->Reset();
	intake->intakeEncoder->Start();
	on = false;
}

// Called repeatedly when this Command is scheduled to run
void SpinIntake::Execute() {
	on = oi->intakeTrigger->Get();
	intake->TakeBall(on);
}

// Make this return true when this Command no longer needs to run execute()
bool SpinIntake::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void SpinIntake::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SpinIntake::Interrupted() {
	
}

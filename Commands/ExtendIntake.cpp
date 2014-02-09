/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li                                                       */
/*-------------------------------------------------------------------------*/

#include "ExtendIntake.h"

ExtendIntake::ExtendIntake() {
	Requires(intake);
}

// Called just before this Command runs the first time
void ExtendIntake::Initialize() {
	intake->ExtendArms();
}

// Called repeatedly when this Command is scheduled to run
void ExtendIntake::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool ExtendIntake::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ExtendIntake::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ExtendIntake::Interrupted() {
	
}

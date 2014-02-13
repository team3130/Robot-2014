/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li                                                       */
/*-------------------------------------------------------------------------*/

#include "StopIntake.h"

StopIntake::StopIntake() {
	// Use Requires() here to declare subsystem dependencies
	Requires(intake);
}

// Called just before this Command runs the first time
void StopIntake::Initialize() {
	intake->TakeBall(false);
	intake->ExtendArms(false);
}

// Called repeatedly when this Command is scheduled to run
void StopIntake::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool StopIntake::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void StopIntake::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StopIntake::Interrupted() {
	
}
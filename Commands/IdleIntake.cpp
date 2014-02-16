/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li                                                       */
/*-------------------------------------------------------------------------*/

#include "IdleIntake.h"

IdleIntake::IdleIntake() : CommandBase("Idle Intake") {
	Requires(intake);
	SmartDashboard::PutData(this);
}

// Called just before this Command runs the first time
void IdleIntake::Initialize() {
	intake->SetIdle(true);
}
// Called repeatedly when this Command is scheduled to run
void IdleIntake::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool IdleIntake::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void IdleIntake::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IdleIntake::Interrupted() {
	
}

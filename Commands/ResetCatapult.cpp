/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Kevin Bi, James Li                                             */
/*-------------------------------------------------------------------------*/

#include "ResetCatapult.h"

ResetCatapult::ResetCatapult() {
	// Use Requires() here to declare subsystem dependencies
	Requires(shooter);
	SmartDashboard::PutNumber("Reset Time", 1);
}

void ResetCatapult::Reset(){
	moveTime = SmartDashboard::GetNumber("Reset Time");
	shooter->adjustCatapult(-(shooter->getCatapultPosition()), moveTime);
}

// Called just before this Command runs the first time
void ResetCatapult::Initialize() {
	moveTime = SmartDashboard::GetNumber("Reset Time");
}

// Called repeatedly when this Command is scheduled to run
void ResetCatapult::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool ResetCatapult::IsFinished() {
	return shooter->getCatapultPosition() == 0;
}

// Called once after isFinished returns true
void ResetCatapult::End() {
	shooter->adjustCatapult(0, 1);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ResetCatapult::Interrupted() {
	shooter->adjustCatapult(0,1);
}

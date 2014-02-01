/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Kevin Bi, James Li                                             */
/*-------------------------------------------------------------------------*/

#include "MoveCatapult.h"

MoveCatapult::MoveCatapult() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(chassis);
}

// Called just before this Command runs the first time
void MoveCatapult::Initialize() {
	chassis->winchEncoder->Reset();
	chassis->winchEncoder->Start();
	timer.Reset();
	timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void MoveCatapult::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool MoveCatapult::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void MoveCatapult::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveCatapult::Interrupted() {
	
}

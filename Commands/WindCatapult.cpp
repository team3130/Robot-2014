/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Kevin Bi, James Li                                             */
/*-------------------------------------------------------------------------*/

#include "WindCatapult.h"

WindCatapult::WindCatapult() {
	Requires(shooter);
	SmartDashboard::PutNumber("New Catapult Position", 1);
	SmartDashboard::PutNumber("Time to Move Catapult", 1);
}

// Called just before this Command runs the first time
void WindCatapult::Initialize() {
	movePosition = SmartDashboard::GetNumber("New Catapult Position");
	timeLapse = SmartDashboard::GetNumber("Time to Move Catapult");
	shooter->winchEncoder->Reset();
	shooter->winchEncoder->Start();
	shooter->adjustCatapult(movePosition, timeLapse);
}

// Called repeatedly when this Command is scheduled to run
void WindCatapult::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool WindCatapult::IsFinished() {
	return movePosition == shooter->getCatapultPosition();
}

// Called once after isFinished returns true
void WindCatapult::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void WindCatapult::Interrupted() {
	
}

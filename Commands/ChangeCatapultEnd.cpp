/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li                                                       */
/*-------------------------------------------------------------------------*/

#include "ChangeCatapultEnd.h"

ChangeCatapultEnd::ChangeCatapultEnd() {
	Requires(shooter);
	SmartDashboard::PutNumber("End Position", 1);
	SmartDashboard::PutNumber("Time Span", 1);
}

// Called just before this Command runs the first time
void ChangeCatapultEnd::Initialize() {
	endPosition = SmartDashboard::GetNumber("End Position");
	timeSpan = SmartDashboard::GetNumber("Time Span");
	shooter->stopEncoder->Reset();
	shooter->stopEncoder->Start();
	shooter->adjustEnd(endPosition, timeSpan);
}

// Called repeatedly when this Command is scheduled to run
void ChangeCatapultEnd::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool ChangeCatapultEnd::IsFinished() {
	return endPosition == shooter->getEndPosition();
}

// Called once after isFinished returns true
void ChangeCatapultEnd::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ChangeCatapultEnd::Interrupted() {
	
}

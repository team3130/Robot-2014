/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li, Kevin Bi                                             */
/*-------------------------------------------------------------------------*/

#include "AccumulateCatapult.h"
AccumulateCatapult::AccumulateCatapult(const char* name) :	CommandBase(name) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(intake);
	Requires(shooter);
	Requires(stopper);
	shooter->setReady(true);
}

// Called just before this Command runs the first time
void AccumulateCatapult::Initialize() {
	state = 0;
	intake->SetIdle(true);
}

// Called repeatedly when this Command is scheduled to run
void AccumulateCatapult::Execute() {
	shooter->setPinch(false);
	bool shootReady = intake->getReadyToShoot();
	SmartDashboard::PutNumber("Ready to Shoot", shootReady);
	// Unwind to fill up the accumulator
	shooter->setWinchDirect(-.5);
	if (shooter->hasSlack()) {
		shooter->setWinchDirect(0);
		state = 1;
	}
	SmartDashboard::PutNumber("AccumulateCatapult State", state);
	stopper->ProjectSensors();
}

// Make this return true when this Command no longer needs to run execute()
bool AccumulateCatapult::IsFinished() {
	return (state == 1);
}

// Called once after isFinished returns true
void AccumulateCatapult::End() {
	shooter->setWinchDirect(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AccumulateCatapult::Interrupted() {
	End();
}

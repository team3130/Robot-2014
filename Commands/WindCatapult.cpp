/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li, Kevin Bi                                             */
/*-------------------------------------------------------------------------*/

#include "WindCatapult.h"
WindCatapult::WindCatapult(const char* name) :	CommandBase(name) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(intake);
	Requires(shooter);
	shooter->setReady(true);
}

// Called just before this Command runs the first time
void WindCatapult::Initialize() {
	state = 0;
	intake->SetIdle(true);
}

// Called repeatedly when this Command is scheduled to run
void WindCatapult::Execute() {
	shooter->setPinch(false);
	bool shootReady = intake->getReadyToShoot();
	SmartDashboard::PutNumber("Ready to Shoot", shootReady);
	if (state == 0 && shootReady) {
		// Wind forward until we hit the limit switch
		shooter->setWinchDirect(.8);
		if (stopper->armSwitchState()) {
			shooter->setWinchDirect(0);
			state = 1;
		}
	} else if (state == 1) {
		// Unwind to fill up the accumulator
		shooter->setWinchDirect(-.5);
		if (shooter->hasSlack()) {
			shooter->setWinchDirect(0);
			state = 2;
		}
	}
	SmartDashboard::PutNumber("WindCatapult State", state);
	stopper->ProjectSensors();
}

// Make this return true when this Command no longer needs to run execute()
bool WindCatapult::IsFinished() {
	return (state == 2 || fabs(oi->gamepad->GetRawAxis(B_POWERWINCH)) > 0.2);
}

// Called once after isFinished returns true
void WindCatapult::End() {
	shooter->setWinchDirect(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void WindCatapult::Interrupted() {
	End();
}

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
	WaitTime = 1.0;
	Requires(intake);
	Requires(shooter);
	Requires(stopper);
	shooter->setReady(true);
	SmartDashboard::PutNumber("Winch Wait", 1.0);
	timer.Reset();
	done = false;
	//SmartDashboard::PutData(this);
}

// Called just before this Command runs the first time
void WindCatapult::Initialize() {
	state = -3;
	intake->ResetIdleTimer();
	intake->SetIdle(true);
	intake->ExtendArms(true);
	//Makes sure there is a delay for the intake to fall down
	timer.Reset();
	done = false;
	timer.Stop();
	timer.Reset();
	beginWaiting = false;
}

// Called repeatedly when this Command is scheduled to run
void WindCatapult::Execute() {
	shooter->setPinch(false);
	WaitTime = SmartDashboard::GetNumber("Winch Wait");
	bool shootReady = intake->getReadyToShoot();
	SmartDashboard::PutNumber("Ready to Shoot", shootReady);
	intake->SetIdle(true);
	intake->ExtendArms(true);
	//Checks if delay time has been met
	if (state == -3 && shootReady) {
		if (!stopper->armSwitchState()) {
			shooter->setWinchDirect(-.8);
		} else {
			state = -2;
		}
	} else if (state == -2) {
		shooter->setWinchDirect(-.5);
		if (shooter->hasSlack()) {
			shooter->setWinchDirect(0);
			state = -1;
		}
	} else if (state == -1 && shootReady) {
		shooter->setWinchDirect(0);
		state = 0;
	} else {
		shooter->setWinchDirect(0);
		done = true;
	}
	SmartDashboard::PutNumber("Timer Time", timer.Get());
	SmartDashboard::PutNumber("WindCatapult State", state);
	stopper->ProjectSensors();
}

// Make this return true when this Command no longer needs to run execute()
bool WindCatapult::IsFinished() {
	return done;
}

// Called once after isFinished returns true
void WindCatapult::End() {
	shooter->setWinchDirect(0);
	state = -2;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void WindCatapult::Interrupted() {
	End();
}

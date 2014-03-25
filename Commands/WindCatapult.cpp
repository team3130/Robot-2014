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
	waitTimer.Stop();
	waitTimer.Reset();
}

// Called repeatedly when this Command is scheduled to run
void WindCatapult::Execute() {
	shooter->setPinch(false);
	bool shootReady = intake->getReadyToShoot();
	SmartDashboard::PutNumber("Ready to Shoot", shootReady);
	if(oi->manualWinchControl->Get())state = 3;
	if (state == 0 && shootReady) {
		// Wind forward until we hit the limit switch
		shooter->setWinchDirect(.8);
		if (stopper->armSwitchState()) {
			shooter->setWinchDirect(0);
			state = 1;
		}
		waitTimer.Start();
	} else if (state == 1) {
		// Make sure it's accumulated. wait for 0.4 seconds.
		if (stopper->armSwitchState()) {
			shooter->setWinchDirect(0);
		}else{
			shooter->setWinchDirect(.8);
		}
		if (waitTimer.Get()>=0.0){
			state = 2;
		}
	} else if (state == 2) {
		// Unwind to fill up the accumulator
		shooter->setWinchDirect(-.5);
		if (shooter->hasSlack()) {
			shooter->setWinchDirect(0);
			state = 3;
		}
	}
	SmartDashboard::PutNumber("WindCatapult State", state);
	stopper->ProjectSensors();
}

// Make this return true when this Command no longer needs to run execute()
bool WindCatapult::IsFinished() {
	// <<<<<<< HEAD
	return (state == 3 || oi->manualWinchControl->Get());
	// =======
	// return (state == 3 || fabs(oi->gamepad->GetRawAxis(B_POWERWINCH)) > 0.2);
	// >>>>>>> ecd44206344eff23c6e7a600650baf1d12a23d20
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

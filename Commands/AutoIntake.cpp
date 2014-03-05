/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Mikhail Kyraha                                                 */
/*-------------------------------------------------------------------------*/

#include "AutoIntake.h"

AutoIntake::AutoIntake() : CommandBase("Auto Intake") {
	Requires(intake);
	SmartDashboard::PutData(this);
	SmartDashboard::PutNumber("AutoIntake Step 1",1.0);
	SmartDashboard::PutNumber("AutoIntake Step 2",1.5);
	SmartDashboard::PutNumber("AutoIntake Step 3",2.5);
	SmartDashboard::PutNumber("AutoIntake Step 4",3.0);
}

int AutoIntake::GetPhase() {
	double cTime = loadTimer.Get();
	if(cTime<SmartDashboard::GetNumber("AutoIntake Step 1")) return 0;
	if(cTime<SmartDashboard::GetNumber("AutoIntake Step 2")) return 1;
	if(cTime<SmartDashboard::GetNumber("AutoIntake Step 3")) return 2;
	if(cTime<SmartDashboard::GetNumber("AutoIntake Step 4")) return 3;
	return 5;
}

// Called just before this Command runs the first time
void AutoIntake::Initialize() {
	intake->ExtendArms(true);
	intake->BeaterBar(1);
	loadTimer.Reset();
	loadTimer.Start();
	done = false;
}

// Called repeatedly when this Command is scheduled to run
void AutoIntake::Execute() {
	switch(GetPhase()){
	case 1:
		intake->SetIdle(true);
		break;
	case 2:
		intake->ExtendArms(false);
		break;
	case 3:
		intake->BeaterBar(0);
		intake->SetIdle(true);
		intake->ResetIdleTimer();
		done = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool AutoIntake::IsFinished() {
	return done;
}

// Called once after isFinished returns true
void AutoIntake::End() {
	intake->BeaterBar(0);
	intake->SetIdle(true);
	intake->ResetIdleTimer();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoIntake::Interrupted() {
	End();
}

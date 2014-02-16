/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li, Kevin Bi                                             */
/*-------------------------------------------------------------------------*/

#include "ShootCatapult.h"
ShootCatapult::ShootCatapult() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	WaitTime=1.0;
	Requires(shooter);
	Requires(stopper);
	Requires(intake);
	shooter->setReady(true);
	SmartDashboard::PutNumber("Winch Wait",1.0);
	timer.Reset();
	done=false;
	//SmartDashboard::PutData(this);
}

// Called just before this Command runs the first time
void ShootCatapult::Initialize() 
{
	state=0;
	intake->SetIdle(true);
	intake->ExtendArms(true);
	//Makes sure there is a delay for the intake to fall down
	timer.Reset();
	done=false;
	timer.Stop();
	timer.Reset();
	beginWaiting=false;
}

// Called repeatedly when this Command is scheduled to run
void ShootCatapult::Execute() {
	WaitTime=SmartDashboard::GetNumber("Winch Wait");
	bool shootReady =intake->getReadyToShoot();
	SmartDashboard::PutNumber("Ready to Shoot", shootReady);
	//Checks if delay time has been met
	if(state==0){	//release pinch.
		if(shootReady){
			timer.Reset();
			timer.Start();
			beginWaiting=true;
			shooter->setPinch(true);
			state=1;
			shooter->setWinchDirect(0);
		}
	}else if(state==1){	//wait for .5 seconds
		if(timer.Get()>0.5){
			state=2;
			shooter->setWinchDirect(0);
		}
	}else if(state==2){
		shooter->setWinchDirect(0.3);
	}
	if(fabs(oi->gamepad->GetRawAxis(B_POWERWINCH))>0.2){
		done=true;
	}
	SmartDashboard::PutNumber("Timer Time", timer.Get());
}

// Make this return true when this Command no longer needs to run execute()
bool ShootCatapult::IsFinished() {
	return done;
}

// Called once after isFinished returns true
void ShootCatapult::End() {
	shooter->setPinch(false);
	shooter->setReady(false);
	shooter->setWinchDirect(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShootCatapult::Interrupted() {
	End();
}

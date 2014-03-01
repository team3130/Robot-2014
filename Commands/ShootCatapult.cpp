/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li, Kevin Bi                                             */
/*-------------------------------------------------------------------------*/

#include "ShootCatapult.h"
ShootCatapult::ShootCatapult(const char* name) : CommandBase(name) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(intake);
	Requires(shooter);
	Requires(stopper);
	shooter->setReady(true);
	SmartDashboard::PutNumber("Winch Wait",1.0);
	timer.Reset();
	done=false;
	canIShoot=false;
	//SmartDashboard::PutData(this);
}

// Called just before this Command runs the first time
void ShootCatapult::Initialize() 
{
	done=false;
	timer.Stop();
	timer.Reset();
	state=0;
}

// Called repeatedly when this Command is scheduled to run
void ShootCatapult::Execute() {
	bool shootReady =intake->getReadyToShoot();
	SmartDashboard::PutNumber("Ready to Shoot", shootReady);
	if(state==0){	//release pinch.
		if(shootReady&&canIShoot){
			shooter->setPinch(true);
			timer.Reset();
			timer.Start();
			state=1;
		}
	}else if(state==1){	//wait for the catapult completes the shot
		if(timer.Get()>1.0){
			state=2;
		}
	}else if(state==2){
		shooter->setPinch(false);
		done=true;
	}
	SmartDashboard::PutNumber("Shooter Timer Time", timer.Get());
	SmartDashboard::PutNumber("ShootCatapult State", state);
	stopper->ProjectSensors();
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
	state=0;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShootCatapult::Interrupted() {
	End();
}

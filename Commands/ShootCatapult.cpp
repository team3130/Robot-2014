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
	WaitTime=1.3;
	Requires(shooter);
	Requires(intake);
	shooter->setReady(true);
	SmartDashboard::PutNumber("Winch Wait",1.3);
	timer.Reset();
	done=false;
	SmartDashboard::PutData(this);
}

// Called just before this Command runs the first time
void ShootCatapult::Initialize() 
{
	intake->SetIdle(true);
	intake->ExtendArms(true);
	//Makes sure there is a delay for the intake to fall down
	timer.Reset();
	timer.Start();
	done=false;
	timer.Reset();
	beginWaiting=false;
}

// Called repeatedly when this Command is scheduled to run
void ShootCatapult::Execute() {
	WaitTime=SmartDashboard::GetNumber("Winch Wait");
	bool shootReady =intake->getReadyToShoot();
	SmartDashboard::PutNumber("Ready to Shoot", shootReady);
	//Checks if delay time has been met
	if(shootReady && !beginWaiting){
		timer.Reset();
		timer.Start();
		beginWaiting=true;
		shooter->setPinch(true);
	}if(timer.Get()>WaitTime){
		shooter->setPinch(false);
		done=true;
		timer.Stop();
	}
	SmartDashboard::PutNumber("Timer Time", timer.Get());
}

// Make this return true when this Command no longer needs to run execute()
bool ShootCatapult::IsFinished() {
	return done;
}

// Called once after isFinished returns true
void ShootCatapult::End() {
	//Sets shooter as not ready to shoot. 
	shooter->setReady(false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShootCatapult::Interrupted() {
	
}

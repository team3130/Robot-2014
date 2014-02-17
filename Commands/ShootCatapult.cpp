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
	WaitTime=1.0;
	Requires(intake);
	Requires(shooter);
	Requires(stopper);
	shooter->setReady(true);
	SmartDashboard::PutNumber("Winch Wait",1.0);
	timer.Reset();
	done=false;
	//SmartDashboard::PutData(this);
}

// Called just before this Command runs the first time
void ShootCatapult::Initialize() 
{
	state=-2;
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
	if(state==-2){
		int outputs=0;
		if(!stopper->armSwitchState()){
			shooter->setWinchDirect(-.5);
		}
		else{
			shooter->setWinchDirect(.5);
		}
		if(stopper->armSwitchState() && shooter->hasSlack()){
			state=-1;
		}
	}
	else if(state==-1){
		shooter->setWinchDirect(0);
		done=true;
	}
	else if(state==0){	//release pinch.
		if(shootReady){
			intake->SetIdle(true);
			intake->ExtendArms(true);
			timer.Reset();
			timer.Start();
			beginWaiting=true;
			shooter->setPinch(true);
			state=1;
			shooter->setWinchDirect(0);
		}
	}else if(state==1){	//wait for .5 seconds
		if(timer.Get()>0.5){
			intake->SetIdle(true);
			intake->ExtendArms(true);
			state=2;
			shooter->setWinchDirect(0);
		}
	}else if(state==2){
		if(!stopper->armSwitchState()){
			shooter->setWinchDirect(-.5);
		}
		else{
			shooter->setWinchDirect(.5);
		}
		if(stopper->armSwitchState() && shooter->hasSlack()){
			state=3;
			done=true;
			stopper->Calibrate(shooter->armEncoder->GetDistance());
		}
	}
	int v = stopper->armSwitchState() == 1;
	if(stopper->armSwitchState() == 1)done=true;
	if(fabs(oi->gamepad->GetRawAxis(B_POWERWINCH))>0.2){
		done=true;
	}
	SmartDashboard::PutNumber("Timer Time", timer.Get());
	SmartDashboard::PutNumber("ShootCatapult State", state);
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

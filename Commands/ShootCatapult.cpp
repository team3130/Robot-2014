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
	//Deactivates the intake to move out of way
<<<<<<< HEAD
	intake->ExtendArms(false);
	intake->SetIdle(true);
	//Makes sure there is a delay for the intake to fall down
	timer.Reset();
	timer.Start();
	done=false;
=======

	if(shooter->getReady())
	{
		//Deactivates the intake to move out of way
		if(intake->getExtend() == true)
		{
			IntakeSafe = false;
			intake->ExtendArms(false);
			intake->SetIdle(true);
			//Makes sure there is a delay for the intake to fall down
			timer.Start();
		}
		else
		{
			IntakeSafe = true;
		}
	}
>>>>>>> 955395e11745ae8e33374fdb8bc497ed9c89537d
}

// Called repeatedly when this Command is scheduled to run
void ShootCatapult::Execute() {
	WaitTime=SmartDashboard::GetNumber("Winch Wait");
	bool shootReady =intake->getReadyToShoot();
	SmartDashboard::PutNumber("Ready to Shoot", shootReady);
	//Checks if delay time has been met
<<<<<<< HEAD
	if(timer.Get() >= WaitTime){
		shooter->setPinch(true);
	}if(timer.Get()>WaitTime+1.5){
=======
	if(timer.Get() >= WaitTime)
	{
		//Stops timer
	}if(timer.Get()>WaitTime*2){
>>>>>>> 955395e11745ae8e33374fdb8bc497ed9c89537d
		shooter->setPinch(false);
		done=true;
		timer.Stop();
	}
	SmartDashboard::PutNumber("Timer Time", timer.Get());
}

// Make this return true when this Command no longer needs to run execute()
bool ShootCatapult::IsFinished() {
<<<<<<< HEAD
	return done;
=======
	//If pinch1 is deactivated and pinch2 is active, then end command
	return shooter->getPinch1() == false && shooter->getPinch2() == true;
	if(shooter->getReady()) return shooter->getPinch1() == false && shooter->getPinch2() == true;
	else return true;
>>>>>>> 955395e11745ae8e33374fdb8bc497ed9c89537d
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

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
	WaitTime=2;
	Requires(shooter);
	Requires(intake);
	shooter->setReady(true);
	SmartDashboard::PutNumber("Winch Wait",2);
	timer.Reset();
	done=false;
}

// Called just before this Command runs the first time
void ShootCatapult::Initialize() 
{
	done=false;
	//Deactivates the intake to move out of way
<<<<<<< HEAD
	intake->ExtendArms(false);
	intake->SetIdle(true);
	//Makes sure there is a delay for the intake to fall down
	timer.Reset();
	timer.Start();
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
>>>>>>> 5985738bed1a1f1f96334ae381d8b3c3864fda3e
}

// Called repeatedly when this Command is scheduled to run
void ShootCatapult::Execute() {
	WaitTime=SmartDashboard::GetNumber("Winch Wait");
	//Checks if delay time has been met
	if(timer.Get() >= WaitTime)
	{
<<<<<<< HEAD
		//Release the pinch to shoot
		shooter->setPinch(true);
=======
>>>>>>> 5985738bed1a1f1f96334ae381d8b3c3864fda3e
		//Stops timer
	}if(timer.Get()>WaitTime*2){
		shooter->setPinch(false);
		done=true;
		timer.Stop();
		//Stops timer
		timer.Stop();
		IntakeSafe = true;
	}
	if(IntakeSafe)
	{
		//Release the pinch to shoot
		shooter->setPinch(false);
	}
	SmartDashboard::PutNumber("Timer Time", timer.Get());
}

// Make this return true when this Command no longer needs to run execute()
bool ShootCatapult::IsFinished() {
	//If pinch1 is deactivated and pinch2 is active, then end command
<<<<<<< HEAD
	return done;
=======
	return shooter->getPinch1() == false && shooter->getPinch2() == true;
	if(shooter->getReady()) return shooter->getPinch1() == false && shooter->getPinch2() == true;
	else return true;
>>>>>>> 5985738bed1a1f1f96334ae381d8b3c3864fda3e
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

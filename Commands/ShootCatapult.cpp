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
	Requires(shooter);
	Requires(intake);
	timer.Reset();
}

// Called just before this Command runs the first time
void ShootCatapult::Initialize() 
{
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
}

// Called repeatedly when this Command is scheduled to run
void ShootCatapult::Execute() {
	//Checks if delay time has been met
	if(timer.Get() >= WaitTime)
	{
		//Stops timer
		timer.Stop();
		IntakeSafe = true;
	}
	if(IntakeSafe)
	{
		//Release the pinch to shoot
		shooter->setPinch(false);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ShootCatapult::IsFinished() {
	//If pinch1 is deactivated and pinch2 is active, then end command
	if(shooter->getReady()) return shooter->getPinch1() == false && shooter->getPinch2() == true;
	else return true;
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

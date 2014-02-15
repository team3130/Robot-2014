/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Kevin Bi, James Li                                             */
/*-------------------------------------------------------------------------*/

#include "ResetCatapult.h"

ResetCatapult::ResetCatapult() {
	// Use Requires() here to declare subsystem dependencies
	Requires(shooter);
}

// Called just before this Command runs the first time
void ResetCatapult::Initialize() {
	shooter->setStopSpeed(0);
	//Sets CurAction to Winding
	CurAction = WINDING;
	//Sets to rewind for a certain amount of time
	shooter->setWinchSpeed(WindSpeed);
	//Resets the timer just in case
	timer.Reset();
	if(shooter->getReady())
	{
		shooter->setWinchSpeed(0);
		CurAction = FINISHED; 
	}
}

// Called repeatedly when this Command is scheduled to run
void ResetCatapult::Execute() 
{
	switch(CurAction)
	{
	//Action to do while catapult is winding
	case WINDING:
		//Checks to see if catapult is at start position
		if(shooter->getCatapultPosition() <= 0)
		{
			//Sets winch speed to 0
			shooter->setWinchSpeed(0);
			//Sets CurAction to Pinching
			CurAction = PINCHING;
		}
		break;
	//Activates pinch and sets Winch to unwind
	case PINCHING:
		//Activates pinch
		shooter->setPinch(true);
		//Sets CurAction to Unwinding
		CurAction = UNWINDING;
		//Sets winch to unwind a predetermined amount over a predetermined time
		shooter->setWinchSpeed(UnwindSpeed);
		timer.Start();
		break;
	//Action while Catapult is unwinding
	case UNWINDING:
		//Checks if Winch has moved sufficient amount
		if(timer.Get() >= UnwindTime)
		{
			shooter->setWinchSpeed(0);
			CurAction = FINISHED;
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ResetCatapult::IsFinished() {
	return CurAction == FINISHED;
}

// Called once after isFinished returns true
void ResetCatapult::End() 
{
	//Sets shooter as ready to fire
	if(shooter->getReady() == false) shooter->setReady(true);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ResetCatapult::Interrupted() 
{
	//Stops motor in case command is interrupted
	shooter->setWinchSpeed(0);
}

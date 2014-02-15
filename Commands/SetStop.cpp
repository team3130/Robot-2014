/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: <Kevin Bi>                                                     */
/*-------------------------------------------------------------------------*/

#include "SetStop.h"

SetStop::SetStop(double position) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(shooter);
	//The position that the stop motor will move to (Lob or Shoot)
	Position = position; 
}

// Called just before this Command runs the first time
void SetStop::Initialize() 
{
	//Determines which direction the motor needs to move to get to desired position
	//If current Stop position is greater than wanted position
	if(shooter->getStopPosition() - Position > 0)
	{
		Direction = -1;
	}
	//If current Stop position is less than wanted position
	else if (shooter->getStopPosition() - Position < 0) 
	{
		Direction = 1;
	}
	//If the position is already correct
	else
	{
		Direction = 0;
		Finished = true;
	}
	//Sets the speed of the Stop motor
	shooter->setStopSpeed(Speed * Direction);
}

// Called repeatedly when this Command is scheduled to run
void SetStop::Execute() 
{
	//Checks if Stop Motor is in the right spot
	if(Direction < 0 && shooter->getStopPosition() <= Position)
	{
		//Stops motor
		shooter->setStopSpeed(0);
		Finished = true;
	}
	else if (Direction > 0 && shooter->getStopPosition() >= Position)
	{
		shooter->setStopSpeed(0);
		Finished = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool SetStop::IsFinished() {
	return Finished;
}

// Called once after isFinished returns true
void SetStop::End() 
{
	//Stops StopState
	if(Position == shooter->STOP_LOB_POSITION) shooter->setStopState(shooter->STOP_LOB);
	else if (Position == shooter->STOP_SHOOT_POSITION) shooter->setStopState(shooter->STOP_SHOOT);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetStop::Interrupted() {
	
}

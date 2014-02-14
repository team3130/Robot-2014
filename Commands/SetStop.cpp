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
	Position = position; 
}

// Called just before this Command runs the first time
void SetStop::Initialize() 
{
	if(shooter->getStopPosition() - Position > 0)
	{
		Direction = -1;
	}
	else if (shooter->getStopPosition() - Position < 0) 
	{
		Direction = 1;
	}
	else
	{
		Direction = 0;
		Finished = true;
	}
	shooter->setStopSpeed(Speed * Direction);
}

// Called repeatedly when this Command is scheduled to run
void SetStop::Execute() 
{
	if(Direction < 0 && shooter->getStopPosition() <= Position)
	{
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
	if(Position == shooter->STOP_LOB_POSITION) shooter->setStopState(shooter->STOP_LOB);
	else if (Position == shooter->STOP_SHOOT_POSITION) shooter->setStopState(shooter->STOP_SHOOT);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetStop::Interrupted() {
	
}

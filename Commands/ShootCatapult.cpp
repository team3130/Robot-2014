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
	Requires(shooter, intake);
}

// Called just before this Command runs the first time
void ShootCatapult::Initialize() 
{
	if(!shooter->getReady()) Finished = true;
	else shooter->setPinch(false);
}

// Called repeatedly when this Command is scheduled to run
void ShootCatapult::Execute() {
	if(shooter->getPinch1() == false && shooter->getPinch2() == true)
	{
		Finished = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ShootCatapult::IsFinished() {
	return Finished; 
}

// Called once after isFinished returns true
void ShootCatapult::End() {
	shooter->setReady(false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShootCatapult::Interrupted() {
	
}

/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Mikhail Kyraha                                                 */
/*-------------------------------------------------------------------------*/
#include "DriveLowGear.h"

DriveLowGear::DriveLowGear() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// We don't want to monopolize chassis just to shif gears so no requirements
}

// Called just before this Command runs the first time
void DriveLowGear::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void DriveLowGear::Execute() {
	chassis->ShiftGear(false);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveLowGear::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void DriveLowGear::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveLowGear::Interrupted() {
	End();
}

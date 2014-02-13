/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Mikhail Kyraha                                                 */
/*-------------------------------------------------------------------------*/
#include "DriveHighGear.h"

DriveHighGear::DriveHighGear() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// We don't want to monopolize chassis just to shif gears so no requirements
}

// Called just before this Command runs the first time
void DriveHighGear::Initialize() {
	chassis->ShiftGear(true);
}

// Called repeatedly when this Command is scheduled to run
void DriveHighGear::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool DriveHighGear::IsFinished() {
	return !oi->shifterButton->Get();
}

// Called once after isFinished returns true
void DriveHighGear::End() {
	chassis->ShiftGear(false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveHighGear::Interrupted() {
	End();
}

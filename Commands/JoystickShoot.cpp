/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li                                                       */
/*-------------------------------------------------------------------------*/

#include "JoystickShoot.h"

JoystickShoot::JoystickShoot() {
	Requires(shooter);
}

// Called just before this Command runs the first time
void JoystickShoot::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void JoystickShoot::Execute() {
	if(fabs(oi->gamepad->GetRawAxis(B_POWERWINCH))>0.1){
		shooter->setWinchDirect(oi->gamepad->GetRawAxis(B_POWERWINCH));
	}else shooter->setWinchDirect(0);

	if(fabs(oi->gamepad->GetRawAxis(B_STOPPERWINCH))>0.1){
		shooter->setStopperDirect(oi->gamepad->GetRawAxis(B_STOPPERWINCH));
	}else shooter->setStopperDirect(0);

	if(oi->gamepad->GetRawButton(B_SHOOT)){
		shooter->UnlockPincher();
	}
	if(oi->gamepad->GetRawButton(B_LOCKSHOOTER)){
		shooter->LockPincher();
	}
	shooter->ProjectSensors();
}

// Make this return true when this Command no longer needs to run execute()
bool JoystickShoot::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void JoystickShoot::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void JoystickShoot::Interrupted() {
	
}

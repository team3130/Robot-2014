/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li                                                       */
/*-------------------------------------------------------------------------*/

#include "JoystickStopperWinch.h"

JoystickStopperWinch::JoystickStopperWinch() : CommandBase("Manual ") {
	Requires(intake);
	stopper->stopperEncoder->Reset();
	stopper->stopperEncoder->Start();
}

// Called just before this Command runs the first time
void JoystickStopperWinch::Initialize() {
}
// Called repeatedly when this Command is scheduled to run
void JoystickStopperWinch::Execute() {
	static bool beaterup=false;
	static bool extendPressed=false;
	if(fabs(oi->gamepad->GetRawAxis(B_STOPPERWINCH))>0.2){
		stopper->setStopperDirect(oi->gamepad->GetRawAxis(B_STOPPERWINCH)/1.65);
	}else stopper->setStopperDirect(0);
}

// Make this return true when this Command no longer needs to run execute()
bool JoystickStopperWinch::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void JoystickStopperWinch::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void JoystickStopperWinch::Interrupted() {
	
}

/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li                                                       */
/*-------------------------------------------------------------------------*/

#include "JoystickIntake.h"

JoystickIntake::JoystickIntake() : CommandBase("Manual Intake") {
	Requires(intake);
}

// Called just before this Command runs the first time
void JoystickIntake::Initialize() {
}
// Called repeatedly when this Command is scheduled to run
void JoystickIntake::Execute() {
	if(oi->gamepad->GetRawButton(B_EXTENDARMS)){
		intake->SetIdle(false);
		intake->ExtendArms(true);
	}
	if(oi->gamepad->GetRawButton(B_RETRACTARMS)){
		intake->SetIdle(false);
		intake->ExtendArms(false);
	}
	if(oi->gamepad->GetRawButton(B_IDLEARMS)){
		intake->SetIdle(true);
	}
	if(oi->gamepad->GetRawButton(B_BEATERBARFWD)){
		intake->BeaterBar(1.0);
	}else intake->BeaterBar(0.0);
	
	/*
	float trigger_beaterbar = oi->gamepad->GetRawAxis(A_BEATERBAR); 
	if(fabs(trigger_beaterbar)>0.5){
		intake->BeaterBar(trigger_beaterbar);
	}
	else {
		intake->BeaterBar(0);
	}
	*/
}

// Make this return true when this Command no longer needs to run execute()
bool JoystickIntake::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void JoystickIntake::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void JoystickIntake::Interrupted() {
	
}

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
	shooter->armEncoder->Reset();
	shooter->stopperEncoder->Reset();
	shooter->armEncoder->Start();
	shooter->stopperEncoder->Start();
}

// Called repeatedly when this Command is scheduled to run
void JoystickShoot::Execute() {
	shooter->setPinch(false);
	SmartDashboard::PutNumber("JoystickShoot Arm Encoder",shooter->armEncoder->GetDistance());
	SmartDashboard::PutNumber("JoystickShoot Stopper Encoder",shooter->stopperEncoder->GetDistance());
	double d= oi->gamepad->GetRawAxis(B_POWERWINCH);
	if(fabs(oi->gamepad->GetRawAxis(B_POWERWINCH))>0.2){
		shooter->setWinchDirect(oi->gamepad->GetRawAxis(B_POWERWINCH)/1.5);
	}else shooter->setWinchDirect(0);

	if(fabs(oi->gamepad->GetRawAxis(B_STOPPERWINCH))>0.2){
		shooter->setStopperDirect(oi->gamepad->GetRawAxis(B_STOPPERWINCH)/1.65);
	}else shooter->setStopperDirect(0);
/*
	if(oi->gamepad->GetRawButton(B_SHOOT)){
		shooter->setPinch(true);
	}else shooter->setPinch(false);
	*/
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

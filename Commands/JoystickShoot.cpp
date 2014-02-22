/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li                                                       */
/*-------------------------------------------------------------------------*/

#include "JoystickShoot.h"

JoystickShoot::JoystickShoot(const char* name) : CommandBase(name) {
	Requires(shooter);
	allInputs = new DigitalInput*[14];
	for(int i=0;i<14;i++){
		allInputs[i]=new DigitalInput(i+1);
	}
}

// Called just before this Command runs the first time
void JoystickShoot::Initialize() {
	shooter->armEncoder->Reset();
	shooter->armEncoder->Start();
}

// Called repeatedly when this Command is scheduled to run
void JoystickShoot::Execute() {
	shooter->setPinch(false);
	SmartDashboard::PutNumber("JoystickShoot Arm Encoder",shooter->armEncoder->GetDistance());
	double d= oi->gamepad->GetRawAxis(B_POWERWINCH);
	if(fabs(d)>0.2){
		shooter->setWinchDirect(d*0.86);
	}else shooter->setWinchDirect(0);
	
	if(oi->gamepad->GetRawButton(B_SHOOT)){
		if(intake->getReadyToShoot()){
			shooter->setPinch(true);
		}else{
			shooter->setPinch(false);
			intake->SetIdle(true);
		}
	}else shooter->setPinch(false);
	
	bool shootReady =intake->getReadyToShoot();
	SmartDashboard::PutNumber("Ready to Shoot", shootReady);
/*
	if(oi->gamepad->GetRawButton(B_SHOOT)){
		shooter->setPinch(true);
	}else shooter->setPinch(false);
	*/
	shooter->ProjectSensors();
	
	char* name = "D. Input    ";
	for(int i=0;i<14;i++){
		name[9]='A'+i;
		SmartDashboard::PutNumber(name, allInputs[i]->Get());
	}
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

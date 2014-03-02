/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li                                                       */
/*-------------------------------------------------------------------------*/

#include "JoystickStopperWinch.h"

JoystickStopperWinch::JoystickStopperWinch() : CommandBase("Manual ") {
	Requires(stopper);
}

// Called just before this Command runs the first time
void JoystickStopperWinch::Initialize() {
	stopper->Calibrate(SmartDashboard::GetNumber("Stopper High Angle"));
	m_position = stopHigh;
	m_manual = false;
	stopper->setSmart(true);
}
// Called repeatedly when this Command is scheduled to run
void JoystickStopperWinch::Execute() {
	if(m_position==stopHigh) {
		if(fabs(oi->gamepad->GetRawAxis(B_STOPPERWINCH))>0.2){
			stopper->setSmart(false);
			stopper->setStopperDirect(oi->gamepad->GetRawAxis(B_STOPPERWINCH)/1.65);
			m_manual = true;
		}
		else if(m_manual) {
			stopper->setStopperDirect(0);
			stopper->Calibrate(SmartDashboard::GetNumber("Stopper High Angle"));
			stopper->setSmart(true);
			m_manual = false;
		}
	}

	if(Robot::StopperEncoderPPI!=0){
		if(oi->gamepad->GetRawButton(B_LOADLOWSHOT)){
			m_manual = false;
			m_position = stopLow;
			stopper->setGoalAngle(SmartDashboard::GetNumber("Stopper Low Angle"));
		}
		if(oi->gamepad->GetRawButton(B_LOADHIGHSHOT)){
			m_manual = false;
			m_position = stopHigh;
			stopper->setGoalAngle(SmartDashboard::GetNumber("Stopper High Angle"));
		}
	}

	stopper->ProjectSensors();
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

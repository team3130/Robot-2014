/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li                                                       */
/*-------------------------------------------------------------------------*/

#include "JoystickStopperWinch.h"

JoystickStopperWinch::JoystickStopperWinch() : CommandBase("Manual ") {
	Requires(stopper);
	stopper->stopperEncoder->Reset();
	stopper->stopperEncoder->Start();
	SmartDashboard::PutNumber("StopperWinch Low Position",-15);
	SmartDashboard::PutNumber("StopperWinch High Position",0);
}

// Called just before this Command runs the first time
void JoystickStopperWinch::Initialize() {
	Robot::preferences->GetBoolean("Arm Encoder Functional", false);
	Robot::preferences->GetBoolean("Stopper Winch Encoder Functional", true);
	stopper->Calibrate(0);		//todo REMOVE THS LINE. PUT IN AUTONOMOUS.
}
// Called repeatedly when this Command is scheduled to run
void JoystickStopperWinch::Execute() {
	//if(!Robot::preferences->GetBoolean("Stopper Winch Encoder Functional")){
	if(false){
		static bool buttondown=false;
		static Timer timer;
		static double mytime=0;
		static double direction=1;
		stopper->setSmart(false);
		if(fabs(oi->gamepad->GetRawAxis(B_STOPPERWINCH))>0.2 
				&& oi->gamepad->GetRawAxis(B_STOPPERWINCH)*direction>0){
			if(buttondown==false){
				timer.Reset();
				timer.Start();
			}
			//stopper->setStopperDirect(oi->gamepad->GetRawAxis(B_STOPPERWINCH)/1.65);
			if(oi->gamepad->GetRawAxis(B_STOPPERWINCH)>0){
				stopper->setStopperDirect(0.4);
				direction=1;
			}else{
				stopper->setStopperDirect(-0.4);
				direction=-1;
			}
			buttondown=true;
		}else {
			if(buttondown==true){
				mytime+=direction*timer.Get();
			}
			stopper->setStopperDirect(0);
			buttondown=false;
			if(fabs(oi->gamepad->GetRawAxis(B_STOPPERWINCH))>0.2){
				if(oi->gamepad->GetRawAxis(B_STOPPERWINCH)>0){
					direction=1;
				}else{
					direction=-1;
				}
			}
		}
		SmartDashboard::PutNumber("Stopper held down",mytime);
	}
	//else if(Robot::preferences->GetBoolean("Stopper Winch Encoder Functional")){
	else{
		stopper->setSmart(true);
		if(oi->gamepad->GetRawButton(B_LOADLOWSHOT)){
			stopper->setGoalInches(SmartDashboard::GetNumber("StopperWinch Low Position"));
		}if(oi->gamepad->GetRawButton(B_LOADHIGHSHOT)){
			stopper->setGoalInches(SmartDashboard::GetNumber("StopperWinch High Position"));
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

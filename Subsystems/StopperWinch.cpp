/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li, Zhenghao Zhu                                         */
/*-------------------------------------------------------------------------*/

#include "StopperWinch.h"
#include "../Robotmap.h"
#include "../Commands/JoystickStopperWinch.h"
#include "math.h"

StopperWinch::StopperWinch() : Subsystem("StopperWinch") {
	stopperEncoder = new Encoder(C_ENCODER_STOPPER_A,C_ENCODER_STOPPER_B,true);
	stopperEncoder->SetDistancePerPulse(114.53);
	armEncoder = new Encoder(C_ENCODER_CATAPULT_A,C_ENCODER_CATAPULT_B,false);
	stopper = new Talon(C_STOPPERMOTOR);
	limitSwitch =new DigitalInput(C_ARM_SWITCH);
	calibratedWithArm=false;
}
StopperWinch::~StopperWinch(){
	//delete winchEncoder;
	delete stopper;
	delete armEncoder;
	delete stopperEncoder;
}
void StopperWinch::InitDefaultCommand(){
	SetDefaultCommand(new JoystickStopperWinch());
}
void StopperWinch::setStopperDirect(double speed){
	stopper->Set(speed);
}
void StopperWinch::ProjectSensors(){
	SmartDashboard::PutNumber("StopperWinch Distance", stopperEncoder->GetDistance());
	SmartDashboard::PutNumber("StopperWinch Arm2 Encoder", armEncoder->GetDistance());
	SmartDashboard::PutBoolean("StopperWinch Arm Switch", limitSwitch->Get());
}
void StopperWinch::setGoal(double angle){
	
}

//Get/set methods
double StopperWinch::getCatapultPosition(){
	
}
double StopperWinch::getStopPosition(){
	
}
bool StopperWinch::armSwitchState(){
	return limitSwitch->Get();
}
//double getWinchPosition();
bool StopperWinch::getReady(){
	
}
int StopperWinch::getStopState(){}

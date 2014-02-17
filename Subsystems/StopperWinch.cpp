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

StopperWinch::StopperWinch() : PIDSubsystem("StopperWinch",0.5,0,0) {
	stopperEncoder = new Encoder(C_ENCODER_STOPPER_A,C_ENCODER_STOPPER_B,true);
	armEncoder = new Encoder(C_ENCODER_CATAPULT_A,C_ENCODER_CATAPULT_B,false);
	stopper = new Talon(C_STOPPERMOTOR);
	limitSwitch =new DigitalInput(C_ARM_SWITCH);
	calibratedWithArm=false;
	SetAbsoluteTolerance(0.4);
	PIDSubsystem::Disable();
}
StopperWinch::~StopperWinch(){
	//delete winchEncoder;
	delete stopper;
	delete armEncoder;
	delete stopperEncoder;
}
void StopperWinch::InitDefaultCommand(){
	stopperEncoder->SetDistancePerPulse(1.0/CommandBase::preferences->GetDouble("StopperEncoderPPI",114.53));
	SetDefaultCommand(new JoystickStopperWinch());
}
void StopperWinch::setStopperDirect(double speed){
	stopper->Set(speed);
}
void StopperWinch::ProjectSensors(){
	SmartDashboard::PutNumber("StopperWinch Distance", stopperEncoder->GetDistance());
	SmartDashboard::PutNumber("StopperWinch Arm2 Encoder", armEncoder->GetDistance());
	SmartDashboard::PutBoolean("StopperWinch Arm Switch", (limitSwitch->Get()?true:false));
}
void StopperWinch::setGoal(double angle){
	//do math here.
	SetSetpoint(DegreesToInches(angle)-DegreesToInches(m_zero));
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

void StopperWinch::Calibrate(double angle){
	stopperEncoder->Reset();
	m_zero = angle;
	SetSetpoint(0);
	Enable();
}

double StopperWinch::ReturnPIDInput(){
	return stopperEncoder->GetDistance();
}
void StopperWinch::UsePIDOutput(double output){
	stopper->Set(output);
}

double StopperWinch::DegreesToInches(double angle){
	return sqrt(
			N_FRAME_L*N_FRAME_L + N_FRAME_ARMLENGTH*N_FRAME_ARMLENGTH -
			2.0*N_FRAME_L*N_FRAME_ARMLENGTH*cos(
				asin(N_FRAME_H/N_FRAME_L) + angle*3.141592653589/180.0
			)
		);
}
double StopperWinch::InchesToDegrees(double inches){
	return 0;
}

/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li, Zhenghao Zhu                                         */
/*-------------------------------------------------------------------------*/

#include "StopperWinch.h"
#include "../Robot.h"
#include "../Commands/JoystickStopperWinch.h"
#include "math.h"

StopperWinch::StopperWinch() : PIDSubsystem("StopperWinch",0.5,0,0) {
	stopperEncoder = new Encoder(C_ENCODER_STOPPER_A,C_ENCODER_STOPPER_B,false);
	armEncoder = new Encoder(C_ENCODER_CATAPULT_A,C_ENCODER_CATAPULT_B,false);
	stopper = new Talon(C_STOPPERMOTOR);
	limitSwitch =new DigitalInput(C_ARM_SWITCH);
	calibratedWithArm=false;
	SetAbsoluteTolerance(0.1);
	PIDSubsystem::Disable();
	SmartDashboard::PutNumber("Stopper Low Angle",26.0);
	SmartDashboard::PutNumber("Stopper High Angle",50.5);
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
	SmartDashboard::PutBoolean("StopperWinch Arm Switch", (limitSwitch->Get()?true:false));
}
void StopperWinch::setGoalAngle(double angle){
	SetSetpoint(DegreesToInches(angle)-DegreesToInches(m_zero));
}
void StopperWinch::setGoalInches(double in){
	SetSetpoint(in);
}

bool StopperWinch::armSwitchState(){
	return (limitSwitch->Get()?true:false);
}

void StopperWinch::Calibrate(double angle){
	m_zero = angle;
	SetSetpoint(0);
	if(Robot::StopperEncoderPPI!=0){
		stopperEncoder->SetDistancePerPulse(1.0/Robot::StopperEncoderPPI);
		stopperEncoder->Reset();
		stopperEncoder->Start();
		Enable();
	}
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
				asin(N_FRAME_H/N_FRAME_L) + angle*M_PI/180.0
			)
		);
}

double StopperWinch::InchesToDegrees(double inches){
	return 0;
}

void StopperWinch::setSmart(bool smart){
	if(smart&&(Robot::StopperEncoderPPI!=0))PIDSubsystem::Enable();
	else PIDSubsystem::Disable();
}

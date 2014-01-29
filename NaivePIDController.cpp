/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty, Mikhail Kyraha                                  */
/*-------------------------------------------------------------------------*/

#include "NaivePIDController.h"

NaivePIDController::NaivePIDController(string vname){
	currentError=0;
	setPoint=0;
	P=0; I=0; D=0;
	accum=0;
	lastSetTime=0;
	lastError=0;
	this->name=vname;
	//SmartDashboard::PutString(string("Output"), //SmartDashboard::GetString("Output")+"\tNPC "+vname+". ");
	projectPIDValues();
	timer.Reset();
	timer.Start();
}
void NaivePIDController::setSetPoint(float in){
	setPoint=in;
}
/**
 * returns the value to set the controller to. Input time in milliseconds
 */
float NaivePIDController::update(float value, long time){
	//update values in //SmartDashboard
	if(timer.Get()>0.5){
		getPIDValues();
		projectPIDValues();
		timer.Stop();
		timer.Reset();
		timer.Start();
	}
	//do math
	lastError = currentError;
	currentError = value- setPoint;
	float propTerm = currentError*P;
	float lastTimeSeconds = ((float)(time-lastSetTime))/1000.f;
	if(lastSetTime==0)lastSetTime=time;
	else{
		accum += lastTimeSeconds*currentError;		//in units of Value * seconds
	}
	float intTerm = I*accum;
	float devTerm = D*((currentError-lastError)/lastTimeSeconds);
	
	return propTerm+intTerm+devTerm;
}
void NaivePIDController::projectPIDValues(){
	printf("Projecting PID values");
	printf(name.c_str());
	printf("\r\n");
	SmartDashboard::PutNumber(name+std::string(" P"),P*1000.);
	SmartDashboard::PutNumber(name+std::string(" I"),I*1000.);
	SmartDashboard::PutNumber(name+std::string(" D"),D*1000.);
	SmartDashboard::PutNumber(name+std::string(" Error"),currentError);
	SmartDashboard::PutNumber(name+std::string(" Accum"),accum);
	SmartDashboard::PutNumber(name+std::string(" DiffError"),currentError-lastError);
}
void NaivePIDController::getPIDValues(){
//	P=-0.001f;
//	I=0;
//	D=0;
	P = SmartDashboard::GetNumber(name+std::string(" P"))/1000.;
	I = SmartDashboard::GetNumber(name+std::string(" I"))/1000.;
	D = SmartDashboard::GetNumber(name+std::string(" D"))/1000.;
}
void NaivePIDController::resetTime(){
	lastError=0;
	currentError=0;
	lastSetTime=0;
}
void NaivePIDController::reset(){
	accum=0;
	lastError=0;
	currentError=0;
	lastSetTime=0;
}
void NaivePIDController::set(float P, float I, float D){
	this->P=P;
	this->I=I;
	this->D=D;
}

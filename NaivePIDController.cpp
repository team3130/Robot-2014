#include "NaivePIDController.h"

NaivePIDController::NaivePIDController(string vname){
	currentError=0;
	setPoint=0;
	P=0; I=0; D=0;
	accum=0;
	lastSetTime=0;
	lastError=0;
	this->name=name;
	SmartDashboard::PutString(string("Output"), SmartDashboard::GetString("Output")+"\tNPC "+vname+". ");
	projectPIDValues();
}
void NaivePIDController::setSetPoint(float in){
	setPoint=in;
}
/**
 * returns the value to set the controller to. Input time in milliseconds
 */
float NaivePIDController::update(float value, long time){
	//update values in SmartDashboard
	getPIDValues();
	projectPIDValues();
	
	//do math
	lastError= currentError;
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
	SmartDashboard::PutNumber(name+std::string(" P"),P);
	SmartDashboard::PutNumber(name+std::string(" I"),I);
	SmartDashboard::PutNumber(name+std::string(" D"),D);
}
void NaivePIDController::getPIDValues(){
	P = SmartDashboard::GetNumber(name+std::string(" P"));
	I = SmartDashboard::GetNumber(name+std::string(" I"));
	D = SmartDashboard::GetNumber(name+std::string(" D"));
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

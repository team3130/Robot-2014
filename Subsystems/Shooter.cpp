/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Kevin Bi, James Li, Zhenghao Zhu                               */
/*-------------------------------------------------------------------------*/

#include "Shooter.h"
#include "../Robotmap.h"
#include "../Commands/ResetCatapult.h"
#include "math.h"

Shooter::Shooter(int winchMotorChannel, int stopMotorChannel, int shootChannel) : Subsystem("Shooter") {
	winchEncoder = new Encoder(C_ENCODER_WINCH_CHANNEL_A, C_ENCODER_WINCH_CHANNEL_B, false);
	stopEncoder = new Encoder(C_ENCODER_STOP_CHANNEL_A, C_ENCODER_WINCH_CHANNEL_B, false);
	pinch = new Solenoid(shootChannel);
	winch = new Jaguar(winchMotorChannel);
	stop = new Jaguar(stopMotorChannel);
	//catapult position 0 considered to be catapult completely winded back
	winchPosition = 0;
	pinch->Set(false);
}

Shooter::~Shooter(){
	delete winchEncoder;
	delete stopEncoder;
	delete pinch;
	delete winch;
	delete stop;
}

void Shooter::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new ResetCatapult());
}

void Shooter::adjustCatapult(double newWinchPosition, double time){
	//code to change position of catapult arm by getting difference
	//and time and setting the speed to those values
	if(time == 0)
	{
		winch->SetSpeed(0);
		return;
	}
	if(fabs(time) < 0.01) time = 1; //to prevent divide by 0 errors
	if(newWinchPosition > 1) newWinchPosition = 1;
	if(newWinchPosition < -1) newWinchPosition = -1;
	
	double difference = newWinchPosition - winchPosition;
	winch->SetSpeed((float)difference/time);
	winchPosition = newWinchPosition;
}

void Shooter::adjustEnd(double newEndPosition, double time)
{
	//code changes end position of catapult arm through
	//difference and time and setting speed
	if(fabs(time) < 0.01) time = 1; //to prevent divide by 0 errors
	if(newEndPosition > 1) newEndPosition = 1;
	if(newEndPosition < -1) newEndPosition = -1;
	
	double difference = newEndPosition - endPosition;
	stop->SetSpeed((float)difference/time);
	endPosition = newEndPosition;
}

void Shooter::setWinchSpeed(double speed){
	winch->SetSpeed((float)speed);
}

void Shooter::setStopSpeed(double speed){
	stop->SetSpeed((float)speed);
}

void Shooter::setShoot(bool toggle){
	pinch->Set(toggle);
}

double Shooter::getWinchPosition()
{
	return winchPosition;
}

void Shooter::setWinchPosition(double pos)
{
	winchPosition = pos;
}
double Shooter::getEndPosition()
{
	return endPosition;
}

double Shooter::getCatapultPosition()
{
	//Get Catapult arm encoder
}
bool Shooter::getPinch()
{
	return pinch->Get();
}

void Shooter::setPinch(bool on)
{
	pinch->Set(on);
}

void Shooter::setReady(bool value)
{
	Ready = value;
}

bool Shooter::getReady()
{
	return Ready; 
}


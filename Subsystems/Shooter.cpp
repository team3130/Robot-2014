/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Kevin Bi, James Li, Zhenghao Zhu                               */
/*-------------------------------------------------------------------------*/

#include "Shooter.h"
#include "../Robotmap.h"
#include "../Commands/ShootCatapult.h"
#include "math.h"

Shooter::Shooter(int winchMotorChannel, int stopMotorChannel, int shootChannel) : Subsystem("Shooter") {
	winchEncoder = new Encoder(C_ENCODER_WINCH_CHANNEL_A, C_ENCODER_WINCH_CHANNEL_B, false);
	stopEncoder = new Encoder(C_ENCODER_STOP_CHANNEL_A, C_ENCODER_WINCH_CHANNEL_B, false);
	shoot = new Solenoid(shootChannel);
	winch = new Jaguar(winchMotorChannel);
	stop = new Jaguar(stopMotorChannel);
	//catapult position 0 considered to be catapult completely winded back
	catapultPosition = 0;
	toggle = false;
	shoot->Set(toggle);
}

Shooter::~Shooter(){
	delete winchEncoder;
	delete stopEncoder;
	delete shoot;
	delete winch;
	delete stop;
}

void Shooter::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new ShootCatapult());
}

void Shooter::adjustCatapult(double newCatapultPosition, double time){
	//code to change position of catapult arm by getting difference
	//and time and setting the speed to those values
	if(fabs(time) < 0.01) time = 1; //to prevent divide by 0 errors
	if(newCatapultPosition > 1) newCatapultPosition = 1;
	if(newCatapultPosition < -1) newCatapultPosition = -1;
	
	double difference = newCatapultPosition - catapultPosition;
	winch->SetSpeed((float)difference/time);
	catapultPosition = newCatapultPosition;
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

void Shooter::Shoot(){
	//In theory, switches toggle of the shoot mechanism and sets the solenoid to that
	toggle = !toggle;
	shoot->Set(toggle);
}

double Shooter::getCatapultPosition()
{
	return catapultPosition;
}

double Shooter::getEndPosition()
{
	return endPosition;
}

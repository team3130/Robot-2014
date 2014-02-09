/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li, Zhenghao Zhu                                         */
/*-------------------------------------------------------------------------*/

#include "Shooter.h"
#include "../Robotmap.h"
#include "../Commands/ShootCatapult.h"
#include "math.h"

Shooter::Shooter(int winchMotorChannel, int shootChannel) : Subsystem("Shooter") {
	winchEncoder = new Encoder(C_ENCODER_WINCH_CHANNEL_1, C_ENCODER_WINCH_CHANNEL_2, false);
	shoot = new Solenoid(shootChannel);
	winch = new Jaguar(winchMotorChannel);
	catapultPosition = 0;
	toggle = false;
	shoot->Set(toggle);
}

Shooter::~Shooter(){
	delete winchEncoder;
	delete shoot;
	delete winch;
}

void Shooter::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new ShootCatapult());
}

void Shooter::adjustCatapult(double difference, double time){
	//experimental code to change position of catapult arm by
	//getting difference and time and setting the DistancePerPulse to those values
	double newCatapultPosition = catapultPosition + difference;
	
	if(fabs(time) < 0.01) time = 0.5;
	if(newCatapultPosition > 1) newCatapultPosition = 1;
	if(newCatapultPosition < -1) newCatapultPosition = -1;
	
	winch->SetSpeed((float)difference/time);
	catapultPosition = newCatapultPosition;
}

void Shooter::Shoot(){
	//In theory, switches toggle of the shoot mechanism and sets the solenoid to that
	toggle = !toggle;
	shoot->Set(toggle);
}


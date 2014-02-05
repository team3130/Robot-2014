/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li, Zhenghao Zhu                                         */
/*-------------------------------------------------------------------------*/

#include "Shooter.h"
#include "../Robotmap.h"
#include "../Commands/ShootCatapult.h"

Shooter::Shooter(int winchMotorChannel, int shootChannel) : Subsystem("Shooter") {
	winchEncoder = new Encoder(C_ENCODER_WINCH_CHANNEL_1, C_ENCODER_WINCH_CHANNEL_2, false);
	shoot = new Solenoid(shootChannel);
	winch = new Jaguar(winchMotorChannel);
	toggle = false;
	shoot->Set(toggle);
}
    
void Shooter::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new ShootCatapult());
}

void Shooter::adjustCatapult(double level){
	double catapultPosition = winchEncoder->GetDistance();
	catapultPosition += level;
}

void Shooter::Shoot(){
	//switches the toggle of the shoot mechanism and sets the solenoid to that in theory
	toggle = !toggle;
	shoot->Set(toggle);
}


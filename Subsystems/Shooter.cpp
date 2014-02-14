/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li, Zhenghao Zhu                                         */
/*-------------------------------------------------------------------------*/

#include "Shooter.h"
#include "../Robotmap.h"
#include "../Commands/JoystickShoot.h"
#include "math.h"

Shooter::Shooter(int winchMotorChannel, int shootChannel1, int shootChannel2) : Subsystem("Shooter") {
	winchEncoder = new Encoder(C_ENCODER_WINCH_CHANNEL_1, C_ENCODER_WINCH_CHANNEL_2, false);
	stopperEncoder = new Encoder(C_ENCODER_STOPPER_A,C_ENCODER_STOPPER_B,false);
	armEncoder = new Encoder(C_ENCODER_CATAPULT_A,C_ENCODER_CATAPULT_B,false);
	shoot1 = new Solenoid(shootChannel1);
	shoot2 = new Solenoid(shootChannel2);
	winch = new Jaguar(winchMotorChannel);
	stopper = new Talon(C_STOPPERMOTOR);
	catapultPosition = 0;
	toggle = false;
	shoot1->Set(toggle);
	shoot2->Set(!toggle);
}

Shooter::~Shooter(){
	delete winchEncoder;
	delete winch;
	delete shoot1;
	delete shoot2;
	delete stopper;
	delete armEncoder;
	delete stopperEncoder;
}

void Shooter::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new JoystickShoot());
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
void Shooter::setWinchDirect(double speed){
	winch->SetSpeed(speed);
}

void Shooter::setStopperDirect(double speed){
	stopper->SetSpeed(speed);
}

void Shooter::SetShoot(bool in){
	//In theory, switches toggle of the shoot mechanism and sets the solenoid to that
	toggle = !toggle;
	shoot1->Set(toggle);
	shoot2->Set(!toggle);
}

void Shooter::LockPincher(bool lock){
	shoot1->Set(lock);
	shoot2->Set(!lock);
}

void Shooter::ProjectSensors() {
	SmartDashboard::PutNumber("Shooter Arm Angle", armEncoder->GetRaw());
	SmartDashboard::PutNumber("Shooter Winch Rope", winchEncoder->GetRaw());
	SmartDashboard::PutNumber("Shooter Stopper Rope", stopperEncoder->GetRaw());
}

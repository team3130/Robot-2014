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
	pinch1 = new Solenoid(shootChannel1);
	pinch2 = new Solenoid(shootChannel2);
	winch = new Jaguar(winchMotorChannel);
	stopper = new Talon(C_STOPPERMOTOR);
	catapultPosition = 0;
	toggle = false;
	pinch1->Set(toggle);
	pinch2->Set(!toggle);
}

Shooter::~Shooter(){
	delete winchEncoder;
	delete winch;
	delete pinch1;
	delete pinch2;
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
	pinch1->Set(toggle);
	pinch2->Set(!toggle);
}

void Shooter::LockPincher(bool lock){
	pinch1->Set(lock);
	pinch2->Set(!lock);
}

void Shooter::ProjectSensors() {
	SmartDashboard::PutNumber("Shooter Arm Angle", armEncoder->GetRaw());
	SmartDashboard::PutNumber("Shooter Winch Rope", winchEncoder->GetRaw());
	SmartDashboard::PutNumber("Shooter Stopper Rope", stopperEncoder->GetRaw());
}

//Get/set methods
double Shooter::getCatapultPosition()
{
	return armEncoder->Get();
}

double Shooter::getWinchPosition()
{
	return winchEncoder->Get();
}

double Shooter::getStopPosition()
{
	return stopperEncoder->Get();
}

bool Shooter::getPinch1()
{
	return pinch1->Get();
}

bool Shooter::getPinch2()
{
	return pinch2->Get();
}

bool Shooter::getReady()
{
	return Ready;
}

void Shooter::setWinchSpeed(double speed)
{
	winch->SetSpeed(speed);
}

void Shooter::setStopSpeed(double speed)
{
	stopper->SetSpeed(speed);
}

void Shooter::setPinch(bool pinch1on)
{
	pinch1->Set(pinch1on);
	pinch2->Set(!pinch1on);
}

void Shooter::setReady(bool value)
{
	Ready = value; 
}

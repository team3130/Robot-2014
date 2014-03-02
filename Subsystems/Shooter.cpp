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
#include "../CommandBase.h"
#include "../Robot.h"
#include "Logger.h"

Shooter::Shooter(int winchMotorChannel, int shootChannel1, int shootChannel2) : Subsystem("Shooter") {
	//winchEncoder = new Encoder(C_ENCODER_WINCH_CHANNEL_1, C_ENCODER_WINCH_CHANNEL_2, false);
	//stopperEncoder = new Encoder(C_ENCODER_STOPPER_A,C_ENCODER_STOPPER_B,true);
//	Arm Encoder:
	/**	POSITIVE VALUES SHOULD CORRESPOND WITH INCREASE IN HEIGHT. POSITIVE AXIS POINTS UPWARD.	**/
	/**	INVERT IF NECESSARY.		**/
	armEncoder = new Encoder(C_ENCODER_CATAPULT_A,C_ENCODER_CATAPULT_B,false);
	pinch1 = new Solenoid(shootChannel1);
	pinch2 = new Solenoid(shootChannel2);
	limitSwitch=new DigitalInput(C_WINCH_TAUT);
	winch = new Jaguar(winchMotorChannel);
	catapultPosition = 0;
	toggle = false;
	pinch1->Set(toggle);
	pinch2->Set(!toggle);
	Ready=true;
	Robot::logger->add_sensor(new Sensor<Encoder>("Shooter.Arm.Encoder.Value", *armEncoder, DOUBLE, &Encoder::GetDistance));

}

Shooter::~Shooter(){
	//delete winchEncoder;
	delete winch;
	delete pinch1;
	delete pinch2;
	delete armEncoder;
}

void Shooter::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new JoystickShoot("Default manual shoot"));
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

void Shooter::SetShoot(bool in){
	//In theory, switches toggle of the shoot mechanism and sets the solenoid to that
	toggle = !toggle;
	pinch1->Set(toggle);
	pinch2->Set(!toggle);
}

//Sets pinch1 and sets pinch2 to the opposite of pinch1
void Shooter::setPinch(bool pinch1on)
{
	LockPincher(pinch1on);
}

void Shooter::LockPincher(bool lock){
	pinch1->Set(lock);
	pinch2->Set(!lock);
}
bool Shooter::hasSlack(){
	return (limitSwitch->Get()?true:false);
}
void Shooter::ProjectSensors() {
	//SmartDashboard::PutNumber("Shooter Arm Angle", armEncoder->GetRaw());
	//SmartDashboard::PutNumber("Shooter Winch Rope", winchEncoder->GetRaw());
	//SmartDashboard::PutNumber("Shooter Stopper Rope", stopperEncoder->GetRaw());
	SmartDashboard::PutBoolean("Shooter Limit Switch", (limitSwitch->Get()?true:false));
	SmartDashboard::PutBoolean("Has Slack", hasSlack());
}
//Get/set methods
double Shooter::getCatapultPosition()
{
	return armEncoder->GetDistance();
}
//Gets whether Pinch1 is active
bool Shooter::getPinch1()
{
	return pinch1->Get();
}

//Gets whether Pinch2 is active
bool Shooter::getPinch2()
{
	return pinch2->Get();
}

//Gets the ready variable
bool Shooter::getReady()
{
	return Ready;
}


//Sets speed of Winch
void Shooter::setWinchSpeed(double speed)
{
	setWinchDirect(speed);
}

//Sets Ready
void Shooter::setReady(bool value)
{
	Ready = value; 
}


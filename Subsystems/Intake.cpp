/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Erin Duebner, James Li                                         */
/*-------------------------------------------------------------------------*/

#include "Intake.h"
#include "../Robotmap.h"
#include "../Commands/SpinIntake.h"
#include "../Commands/JoystickIntake.h"

Intake::Intake() : Subsystem("Intake") {
	intake = new Talon(C_INTAKEMOTOR1);
	extend = new Solenoid(C_EXTENDSOLENOID1);
	idle = new Solenoid(C_IDLESOLENOID);
	idleSet=false;
	extendSet=false;
}

Intake::~Intake(){
	delete intake;
	delete extend;
	delete idle;
}

void Intake::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new JoystickIntake());
}

void Intake::BeaterBar(double speed){
	intake->SetSpeed(speed);
}

void Intake::TakeBall(bool isOn){
	double power = isOn ? 1 : 0;
	intake->SetSpeed(power);
}
void Intake::ExtendArms(bool extended){
	//if the arms are set to extended or idle, then begin the timer.
	//the timer is read in the getReadyToShoot() function. This waits
	//for 1 second until the arms have left the DOWN (un-idled) position
	//until it returns that we can shoot.
	if(extended || idleSet)readyTimer.Start();
	else{	//set to retracted and un-idled.
		readyTimer.Reset();
		readyTimer.Stop();
	}
	extend->Set(extended);
	extendSet=extended;
}
void Intake::SetIdle(bool in){
	if(in==true || extendSet)readyTimer.Start();
	else{	//set to un-idled and retracted.
		readyTimer.Reset();
		readyTimer.Stop();
	}
	idle->Set(in);
	idleSet=in;
}
double Intake::getSpeed(){
	return intake->Get();
}
bool Intake::getExtend(){
	return extend->Get();
}
bool Intake::getIdle(){
	return idle->Get();
}
bool Intake::getReadyToShoot(){
	return readyTimer.Get()>1;	//idle for at least one second.
}

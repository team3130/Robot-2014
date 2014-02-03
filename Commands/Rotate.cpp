/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Mikhail Kyraha                                                 */
/*-------------------------------------------------------------------------*/

#include "Rotate.h"

#include "math.h"
Rotate::Rotate(double dist, double thresh, double timeToWait, double p, double i, double d): PIDCommand("Rotate", p, i, d){
	PIDCommand::Requires(CommandBase::chassis);
	this->chassis = CommandBase::chassis;
	goal=dist;
	distanceToGoal=goal;
	threshold=thresh;
	confirmTime=timeToWait;
	SmartDashboard::PutData(this);
	SmartDashboard::PutNumber("Rotate PID P",-7);
	SmartDashboard::PutNumber("Rotate PID I",0);
	SmartDashboard::PutNumber("Rotate PID D",0);
	SmartDashboard::PutNumber("RotateGoal",90);
}
Rotate::Rotate(double dist, double thresh, double timeToWait): PIDCommand("Rotate", -7,0,0){
	PIDCommand::Requires(CommandBase::chassis);
	this->chassis = CommandBase::chassis;
	goal=dist;
	distanceToGoal=goal;
	threshold=thresh;
	confirmTime=timeToWait;
	SmartDashboard::PutData(this);
	SmartDashboard::PutNumber("Rotate PID P",-7);
	SmartDashboard::PutNumber("Rotate PID I",0);
	SmartDashboard::PutNumber("Rotate PID D",0);
	SmartDashboard::PutNumber("RotateGoal",dist);
	PIDCommand::SetSetpoint(dist);
}
// Called just before this Command runs the first time
void Rotate::Initialize() {
	double np=SmartDashboard::GetNumber("Rotate PID P")/1000.;
	double ni=SmartDashboard::GetNumber("Rotate PID I")/1000.;
	double nd=SmartDashboard::GetNumber("Rotate PID D")/1000.;
	PIDCommand::SetSetpoint(SmartDashboard::GetNumber("RotateGoal"));
	controller=GetPIDController();
	controller->SetPID(np,ni,nd);
	chassis->gyro->Reset();
	chassis->gyro->SetPIDSourceParameter(PIDSource::kAngle);
	timer.Reset();
	timer.Start();
	controller->Reset();
	controller->Enable();
	chassis->resetBias();
	chassis->leftEncoder->Reset();
	chassis->rightEncoder->Reset();
	//GetPIDController()->Reset();
}

// Called repeatedly when this Command is scheduled to run
void Rotate::Execute() {
	double dist = goal-(chassis->gyro->GetAngle());
	distanceToGoal=dist;
	SmartDashboard::PutNumber("Gyro D",chassis->gyro->GetAngle());
	SmartDashboard::PutNumber("Encoder L",chassis->leftEncoder->Get());
	SmartDashboard::PutNumber("Encoder R",chassis->rightEncoder->Get());
	//(4x|x|)/(4x^2+1)
	//This function has no mathematical significance; but because it tapers off near 0, it
	//is preferable to a purely proportional control. This function also has horizontal asymptotes
	//at both -1 and 1. This function rises more gradually than either a quadratic or
	//exponential control.
	//this function assumes distance is in meters.
	//double x= distanceToGoal;
	//if(power<-1)power=-1;
	//if(power>1)power=1;
	//chassis->straightDrive(power);
}

// Make this return true when this Command no longer needs to run execute()
bool Rotate::IsFinished() {
	if(fabs(distanceToGoal)<threshold){
		timer.Start();
	}else{
		timer.Stop();
		timer.Reset();
	}
	if(timer.Get()>=confirmTime)return true;
	else return false;
}
double Rotate::ReturnPIDInput(){
	return chassis->gyro->GetAngle();
}
void Rotate::UsePIDOutput(double output){
	static double lastOutput=0;
	if(output*lastOutput<0){
//		controller->Reset();
//		controller->Enable();
	}
	
	if(output<0.11 && output >0.01)output=0.11;
	if(output>-0.11 && output <-0.01)output=-0.11;
	if(output<-.5)output=-.5;
	if(output>.5)output=0.5;
	
	chassis->tankDrive(output,-output);
	lastOutput=output;
}

// Called once after isFinished returns true
void Rotate::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Rotate::Interrupted() {
	
}

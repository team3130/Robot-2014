/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Mikhail Kyraha                                                 */
/*-------------------------------------------------------------------------*/

#include "Rotate.h"
<<<<<<< HEAD
#include "math.h"
#include "../DoubleEncoder.h"
Rotate::Rotate(double dist, double thresh, double timeToWait, double p, double i, double d): PIDCommand("Rotate", p, i, d){
	PIDCommand::Requires(CommandBase::chassis);
	this->chassis = CommandBase::chassis;
	goal=dist;
	distanceToGoal=goal;
	threshold=thresh;
	confirmTime=timeToWait;
	SmartDashboard::PutData(this);
	SmartDashboard::PutNumber("Rotate PID P",-10000);
	SmartDashboard::PutNumber("Rotate PID I",0);
	SmartDashboard::PutNumber("Rotate PID D",0);
	SmartDashboard::PutNumber("RotateGoal",0.5);
=======

Rotate::Rotate(double angle, double p, double i, double d)
: PIDCommand("Rotate", p, i, d)
{
	Requires(CommandBase::chassis);
	SmartDashboard::PutData(this);
>>>>>>> 47bea4b9c9d7b12b7e1199060397fac8ff3aacdd
}
// Called just before this Command runs the first time
void Rotate::Initialize() {
<<<<<<< HEAD
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
	chassis->resetBias();
=======
	GetPIDController()->Reset();
	GetPIDController()->SetAbsoluteTolerance(SmartDashboard::GetNumber("Rotate Tolerance"));
	SetSetpoint(SmartDashboard::GetNumber("Rotate"));
	GetPIDController()->SetPID(
		SmartDashboard::GetNumber("Rotate PID P"),
		SmartDashboard::GetNumber("Rotate PID I"),
		SmartDashboard::GetNumber("Rotate PID D"));
>>>>>>> 47bea4b9c9d7b12b7e1199060397fac8ff3aacdd
}

// Called repeatedly when this Command is scheduled to run
void Rotate::Execute() {
<<<<<<< HEAD
	double dist = goal-(chassis->leftEncoder->GetDistance()+chassis->rightEncoder->GetDistance())/2.0;
	distanceToGoal=dist;
	SmartDashboard::PutNumber("Gyro D",chassis->gyro->GetAngle());
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
=======
	SmartDashboard::PutNumber("Rotate to go",GetPIDController()->GetError());
>>>>>>> 47bea4b9c9d7b12b7e1199060397fac8ff3aacdd
}

// Make this return true when this Command no longer needs to run execute()
bool Rotate::IsFinished() {
<<<<<<< HEAD
	if(fabs(distanceToGoal)<threshold){
		timer.Start();
	}else{
		timer.Stop();
		timer.Reset();
	}
	if(timer.Get()>=confirmTime)return true;
	else return false;
=======
	return GetPIDController()->OnTarget();
>>>>>>> 47bea4b9c9d7b12b7e1199060397fac8ff3aacdd
}
double Rotate::ReturnPIDInput(){
	//double gyroInput = chassis->gyro->Get
	return chassis->gyro->GetAngle();
}
void Rotate::UsePIDOutput(double output){
	if(fabs(output)>1)controller->Reset();	//i component is too high, or something.
	chassis->tankDrive(output,-output);
}

// Called once after isFinished returns true
void Rotate::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Rotate::Interrupted() {
	
}
double Rotate::ReturnPIDInput(){
	double nowAngle = CommandBase::chassis->gyro->GetAngle();
	double normalizer = SmartDashboard::GetNumber("Rotate Slowdown");
	return normalizer != 0.0 ? nowAngle / normalizer : nowAngle;
}
void Rotate::UsePIDOutput(double output){
	CommandBase::chassis->tankDrive(output,-output);
}

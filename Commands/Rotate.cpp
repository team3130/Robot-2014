/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty, Mikhail Kyraha                                                 */
/*-------------------------------------------------------------------------*/

#include "Rotate.h"
#include "math.h"

// Used to be constructed with (180,2.5,1,-1,0,0)
Rotate::Rotate(): PIDCommand("Rotate", 0, 0, 0){
	PIDCommand::Requires(CommandBase::chassis);
	SmartDashboard::PutData(this);
	SmartDashboard::PutNumber("Rotate PID P",-7);
	SmartDashboard::PutNumber("Rotate PID I",0);
	SmartDashboard::PutNumber("Rotate PID D",0);
	SmartDashboard::PutNumber("Rotate Goal",0);
	SmartDashboard::PutNumber("Rotate Threshold",0);
	SmartDashboard::PutNumber("Rotate Cooldown",0);
}

void Rotate::SetGoal(double dist, double thresh, double timeToWait) {
	dist-=360*((int)(dist/360));	//ensure its absolute value is less than 360.
	if(dist>180)dist-=360;			//choose the shortest direction to the goal
	else if(dist<-180)dist+=360;		//choose the shortest direction to the goal
	
	goal=dist;
	threshold=thresh;
	confirmTime=timeToWait;
	SmartDashboard::PutNumber("Rotate Goal",goal);
	SmartDashboard::PutNumber("Rotate Threshold",thresh);
	SmartDashboard::PutNumber("Rotate Cooldown",timeToWait);
}

// Called just before this Command runs the first time
void Rotate::Initialize() {
	GetPIDController()->Disable();
	double np=SmartDashboard::GetNumber("Rotate PID P")/1000.;
	double ni=SmartDashboard::GetNumber("Rotate PID I")/1000.;
	double nd=SmartDashboard::GetNumber("Rotate PID D")/1000.;
	GetPIDController()->SetPID(np,ni,nd);
	GetPIDController()->SetSetpoint(goal);
	GetPIDController()->SetAbsoluteTolerance(threshold);
	//CommandBase::chassis->leftEncoder->Reset();
	//CommandBase::chassis->rightEncoder->Reset();
	CommandBase::chassis->gyro->Reset();
	CommandBase::chassis->gyro->SetPIDSourceParameter(PIDSource::kAngle);
	CommandBase::chassis->drive->DumbRobot();
	timer.Reset();
	timer.Start();
	GetPIDController()->Reset();
	GetPIDController()->Enable();
}

// Called repeatedly when this Command is scheduled to run
void Rotate::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool Rotate::IsFinished() {
	if(!GetPIDController()->OnTarget()) return isConfirming = false;
	if(!isConfirming) {
		isConfirming = true;
		timer.Reset();
		timer.Start();
	}
	return timer.Get() >= confirmTime;
}
double Rotate::ReturnPIDInput(){
	return CommandBase::chassis->gyro->GetAngle();
}

void Rotate::UsePIDOutput(double output){
	if(output<0.11 && output >0.001)output=0.11;
	if(output>-0.11 && output <-0.001)output=-0.11;
	if(output<-.5)output=-.5;
	if(output>.5)output=0.5;
	
	CommandBase::chassis->tankDrive(output,-output);
}

// Called once after isFinished returns true
void Rotate::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Rotate::Interrupted() {
	
}

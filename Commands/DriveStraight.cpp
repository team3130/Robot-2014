/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty                                                  */
/*-------------------------------------------------------------------------*/
#include "DriveStraight.h"
#include "math.h"

// Used be constructed with (300,0.05,1,0,0,0)
DriveStraight::DriveStraight(const char *name): PIDCommand(name,0,0,0){
	Requires(CommandBase::chassis);
	this->chassis = CommandBase::chassis;
	SmartDashboard::PutData(this);
	SmartDashboard::PutNumber("Straight PID P",-3000);
	SmartDashboard::PutNumber("Straight PID I",0);
	SmartDashboard::PutNumber("Straight PID D",0);
}

void DriveStraight::SetGoal(double dist, double thresh, double timeToWait) {
	goal=dist;
	threshold=thresh;
	confirmTime=timeToWait;
	SmartDashboard::PutNumber(GetName()+"Straight Goal",goal);
	SmartDashboard::PutNumber(GetName()+"Straight Threshold",thresh);
	SmartDashboard::PutNumber(GetName()+"Straight Cooldown",timeToWait);
	GetPIDController()->SetSetpoint(goal);
	GetPIDController()->SetAbsoluteTolerance(threshold);
}

// Called just before this Command runs the first time
void DriveStraight::Initialize() {
	double np=SmartDashboard::GetNumber("Straight PID P")/1000.;
	double ni=SmartDashboard::GetNumber("Straight PID I")/1000.;
	double nd=SmartDashboard::GetNumber("Straight PID D")/1000.;
	GetPIDController()->SetPID(np,ni,nd);
	GetPIDController()->SetSetpoint(goal);
	GetPIDController()->SetAbsoluteTolerance(threshold);
	chassis->InitEncoders();
	chassis->SmartRobot();
}

// Called repeatedly when this Command is scheduled to run
void DriveStraight::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool DriveStraight::IsFinished() {
	if(GetPIDController()->OnTarget()){
		if(!isConfirming) {
			isConfirming = true;
			timer.Reset();
			timer.Start();
		}
		return timer.Get() >= confirmTime;
	}else{
		isConfirming = false;
		timer.Stop();
		timer.Reset();
	}
	return false;
}

double DriveStraight::ReturnPIDInput(){
	double d = chassis->GetDistance();
	SmartDashboard::PutNumber("DriveStraight Position", d);
	SmartDashboard::PutNumber("DriveStraight Goal", GetPIDController()->GetSetpoint());
	return d;
}

void DriveStraight::UsePIDOutput(double output){
	//SmartDashboard::PutNumber("DriveStraight Error", GetPIDController()->GetError());
	//if(output<0.11 && output >0.01)output=0.11;		//magic numbers. worked well in testing.
	//if(output>-0.11 && output <-0.01)output=-0.11;
	chassis->arcadeDrive(output,0);
}

// Called once after isFinished returns true
void DriveStraight::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraight::Interrupted() {
	
}

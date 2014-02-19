/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty                                                  */
/*-------------------------------------------------------------------------*/
#include "DriveStraightGyro.h"
#include "math.h"

// Used be constructed with (300,0.05,1,0,0,0)
DriveStraightGyro::DriveStraightGyro(const char *name): PIDCommand(name,0,0,0){
	Requires(CommandBase::chassis);
	this->chassis = CommandBase::chassis;
	//SmartDashboard::PutData(this);
	SmartDashboard::PutNumber("NO ENCODER Straight PID P",-3000);
	SmartDashboard::PutNumber("NO ENCODER Straight PID I",0);
	SmartDashboard::PutNumber("NO ENCODER Straight PID D",0);
	SetGoal(1,0.8);
	//SmartDashboard::PutData(this);
}

void DriveStraightGyro::SetGoal(double time, double speed) {
	goalTime=time;
	moveSpeed=speed;
	SmartDashboard::PutNumber(GetName()+"NO ENCODER Straight Speed",speed);
	SmartDashboard::PutNumber(GetName()+"NO ENCODER Straight Threshold",time);
	GetPIDController()->SetSetpoint(0);
}

// Called just before this Command runs the first time
void DriveStraightGyro::Initialize() {
	double np=SmartDashboard::GetNumber("NO ENCODER Straight PID P")/1000.;
	double ni=SmartDashboard::GetNumber("NO ENCODER Straight PID I")/1000.;
	double nd=SmartDashboard::GetNumber("NO ENCODER Straight PID D")/1000.;
	GetPIDController()->SetPID(np,ni,nd);
	GetPIDController()->SetSetpoint(0);
	chassis->InitEncoders();
	chassis->DumbRobot();
	timer.Reset();
	timer.Start();
	chassis->gyro->Reset();
}

// Called repeatedly when this Command is scheduled to run
void DriveStraightGyro::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool DriveStraightGyro::IsFinished(){
	SmartDashboard::PutNumber("timer", timer.Get());
	SmartDashboard::PutNumber("goal", goalTime);
	if(timer.Get()>goalTime)return true;
	else return false;
}

double DriveStraightGyro::ReturnPIDInput(){
	return chassis->gyro->GetAngle();
}

void DriveStraightGyro::UsePIDOutput(double output){
	if(timer.Get()<=goalTime){
		chassis->arcadeDrive(moveSpeed,0);
	}
}

// Called once after isFinished returns true
void DriveStraightGyro::End() {
	chassis->arcadeDrive(0,0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraightGyro::Interrupted() {
	End();
}

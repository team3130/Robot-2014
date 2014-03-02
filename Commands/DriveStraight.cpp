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

	SmartDashboard::PutNumber("Straight PID P",-3000);
	SmartDashboard::PutNumber("Straight PID I",0);
	SmartDashboard::PutNumber("Straight PID D",0);
}

void DriveStraight::SetGoal(double dist, double thresh, double timeToWait) {
	goal=dist;
	threshold=thresh;
	confirmTime=timeToWait;
	dumbDriveTime = fabs(dist / Robot::LowGearTopSpeed);
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
	keepAngle = chassis->gyro->GetAngle();
	chassis->InitEncoders();
	chassis->SmartRobot();
	timer.Reset();
	timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void DriveStraight::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool DriveStraight::IsFinished() {
	if(chassis->CanUseEncoders()){
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
	} else {
		return timer.Get()>=dumbDriveTime;
	}
	return false;
}

double DriveStraight::ReturnPIDInput(){
	if(chassis->CanUseEncoders()){
		return chassis->GetDistance();
	} else {
		if(timer.Get()>=dumbDriveTime){
			return goal;
		} else {
			return 0;
		}
	}
}

void DriveStraight::UsePIDOutput(double output){
	double drift = 0;
	if(chassis->CanUseGyro()){
		drift = driftK*(chassis->gyro->GetAngle() - keepAngle)*fabs(output);
	}
	chassis->arcadeDrive(output,drift);
}

// Called once after isFinished returns true
void DriveStraight::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraight::Interrupted() {
	
}

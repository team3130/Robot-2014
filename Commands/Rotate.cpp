/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty, Mikhail Kyraha                                  */
/*-------------------------------------------------------------------------*/

#include "Rotate.h"

// Used to be constructed with (180,2.5,1,-1,0,0)
Rotate::Rotate(const char *name): PIDCommand(name, 0, 0, 0){
	PIDCommand::Requires(CommandBase::chassis);
	SmartDashboard::PutData(this);
	SmartDashboard::PutNumber("Rotate PID P",-7);
	SmartDashboard::PutNumber("Rotate PID I",0);
	SmartDashboard::PutNumber("Rotate PID D",0);
	SmartDashboard::PutNumber("Rotate Goal",0);
	SmartDashboard::PutNumber("Rotate Threshold",0);
	SmartDashboard::PutNumber("Rotate Cooldown",0);
}

void Rotate::SetGoal(double dist, double thresh, double timeToWait, bool resetGyro) {
	goal=ConstrainAngle(dist);
	threshold=thresh;
	confirmTime=timeToWait;
	resetGyroOnInit=true;
	SmartDashboard::PutNumber("Rotate Goal",goal);
	SmartDashboard::PutNumber("Rotate Threshold",thresh);
	SmartDashboard::PutNumber("Rotate Cooldown",timeToWait);
	resetGyroOnInit = resetGyro;
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
	if(resetGyroOnInit)CommandBase::chassis->gyro->Reset();
	CommandBase::chassis->gyro->SetPIDSourceParameter(PIDSource::kAngle);
	CommandBase::chassis->InitEncoders();
	CommandBase::chassis->SmartRobot();
	timer.Reset();
	timer.Start();
	GetPIDController()->Reset();
	GetPIDController()->Enable();
	
	//SmartDashboard::PutNumber("Minimum Rotate Speed", 0.15);
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
	static double pmax=1;
	static double minVoltage = 0.0;
	if(output<minVoltage && output >0.001)output=minVoltage;
	if(output>-minVoltage && output <-0.001)output=-minVoltage;
	if(output<-pmax)output=-pmax;
	if(output>pmax)output=pmax;
	
	CommandBase::chassis->tankDrive(output,-output);
}

// Called once after isFinished returns true
void Rotate::End() {
	//TODO should we check for resetGyroOnInit here too?
	CommandBase::chassis->gyro->Reset();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Rotate::Interrupted() {
	End();
}


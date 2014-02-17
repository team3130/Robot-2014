/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty, Mikhail Kyraha                                  */
/*-------------------------------------------------------------------------*/

#include "StopperWinchControl.h"

// Used to be constructed with (180,2.5,1,-1,0,0)
StopperWinchControl::StopperWinchControl(const char *name): PIDCommand(name, 0, 0, 0){
	//PIDCommand::Requires(CommandBase::chassis);
	//SmartDashboard::PutData(this);
	SmartDashboard::PutNumber("StopperWinchControl PID P",-7);
	SmartDashboard::PutNumber("StopperWinchControl PID I",0);
	SmartDashboard::PutNumber("StopperWinchControl PID D",0);
	SmartDashboard::PutNumber("StopperWinchControl Goal",0);
	SmartDashboard::PutNumber("StopperWinchControl Threshold",0);
	SmartDashboard::PutNumber("StopperWinchControl Cooldown",0);
}

void StopperWinchControl::SetGoal(double dist, double thresh, double timeToWait, bool resetGyro) {
	goal=ConstrainAngle(dist);
	threshold=thresh;
	confirmTime=timeToWait;
	resetGyroOnInit=true;
	SmartDashboard::PutNumber("StopperWinchControl Goal",goal);
	SmartDashboard::PutNumber("StopperWinchControl Threshold",thresh);
	SmartDashboard::PutNumber("StopperWinchControl Cooldown",timeToWait);
	resetGyroOnInit = resetGyro;
}

// Called just before this Command runs the first time
void StopperWinchControl::Initialize() {
	GetPIDController()->Disable();
	double np=SmartDashboard::GetNumber("StopperWinchControl PID P")/1000.;
	double ni=SmartDashboard::GetNumber("StopperWinchControl PID I")/1000.;
	double nd=SmartDashboard::GetNumber("StopperWinchControl PID D")/1000.;
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
	
	//SmartDashboard::PutNumber("Minimum StopperWinchControl Speed", 0.15);
}

// Called repeatedly when this Command is scheduled to run
void StopperWinchControl::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool StopperWinchControl::IsFinished() {
	if(!GetPIDController()->OnTarget()) return isConfirming = false;
	if(!isConfirming) {
		isConfirming = true;
		timer.Reset();
		timer.Start();
	}
	return timer.Get() >= confirmTime;
}
double StopperWinchControl::ReturnPIDInput(){
	return CommandBase::chassis->gyro->GetAngle();
}
void StopperWinchControl::UsePIDOutput(double output){
	static double pmax=1;
	static double minVoltage = 0.0;
	if(output<minVoltage && output >0.001)output=minVoltage;
	if(output>-minVoltage && output <-0.001)output=-minVoltage;
	if(output<-pmax)output=-pmax;
	if(output>pmax)output=pmax;
	
	CommandBase::chassis->tankDrive(output,-output);
}

// Called once after isFinished returns true
void StopperWinchControl::End() {
	//TODO should we check for resetGyroOnInit here too?
	CommandBase::chassis->gyro->Reset();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StopperWinchControl::Interrupted() {
	End();
}


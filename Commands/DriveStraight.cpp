#include "DriveStraight.h"
#include "math.h"
#include "../DoubleEncoder.h"
DriveStraight::DriveStraight(double dist, double thresh, double timeToWait, double p, double i, double d): PIDCommand("Drive Straight", p, i, d){
	PIDCommand::Requires(CommandBase::chassis);
	this->chassis = CommandBase::chassis;
	goal=dist;
	distanceToGoal=goal;
	threshold=thresh;
	confirmTime=timeToWait;
	SmartDashboard::PutData(this);
	SmartDashboard::PutNumber("Straight PID P",-10000);
	SmartDashboard::PutNumber("Straight PID I",0);
	SmartDashboard::PutNumber("Straight PID D",0);
	SmartDashboard::PutNumber("StraightGoal",0.5);
}
// Called just before this Command runs the first time
void DriveStraight::Initialize() {
	double np=SmartDashboard::GetNumber("Straight PID P")/1000.;
	double ni=SmartDashboard::GetNumber("Straight PID I")/1000.;
	double nd=SmartDashboard::GetNumber("Straight PID D")/1000.;
	PIDCommand::SetSetpoint(SmartDashboard::GetNumber("StraightGoal"));
	controller=GetPIDController();
	controller->SetPID(np,ni,nd);
	chassis->leftEncoder->Reset();
	chassis->rightEncoder->Reset();
	chassis->leftEncoder->Start();
	chassis->rightEncoder->Start();
	timer.Reset();
	timer.Start();
	chassis->resetBias();
}

// Called repeatedly when this Command is scheduled to run
void DriveStraight::Execute() {
	double dist = goal-(chassis->leftEncoder->GetDistance()+chassis->rightEncoder->GetDistance())/2.0;
	distanceToGoal=dist;
	SmartDashboard::PutNumber("Straight LE D",chassis->leftEncoder->GetDistance());
	SmartDashboard::PutNumber("Straight RE D",chassis->rightEncoder->GetDistance());
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
bool DriveStraight::IsFinished() {
	if(fabs(distanceToGoal)<threshold){
		timer.Start();
	}else{
		timer.Stop();
		timer.Reset();
	}
	if(timer.Get()>=confirmTime)return true;
	else return false;
}
double DriveStraight::ReturnPIDInput(){
	return (chassis->leftEncoder->GetDistance()+chassis->rightEncoder->GetDistance())/2.0;
}
void DriveStraight::UsePIDOutput(double output){
	chassis->arcadeDrive(output,0);
}

// Called once after isFinished returns true
void DriveStraight::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraight::Interrupted() {
	
}

#include "DriveStraight.h"
#include "math.h"

// Used be constructed with (300,0.05,1,0,0,0)
DriveStraight::DriveStraight(): PIDCommand("Drive Straight",0,0,0){
	Requires(CommandBase::chassis);
	this->chassis = CommandBase::chassis;
	SmartDashboard::PutData(this);
	SmartDashboard::PutNumber("Straight PID P",-3000);
	SmartDashboard::PutNumber("Straight PID I",0);
	SmartDashboard::PutNumber("Straight PID D",0);
	SmartDashboard::PutNumber("StraightGoal",1.0);
}

void DriveStraight::SetGoal(double dist, double thresh, double timeToWait) {
	goal=dist;
	threshold=thresh;
	confirmTime=timeToWait;
	SmartDashboard::PutNumber("Straight Goal",goal);
	SmartDashboard::PutNumber("Straight Threshold",thresh);
	SmartDashboard::PutNumber("Straight Cooldown",timeToWait);
}

// Called just before this Command runs the first time
void DriveStraight::Initialize() {
	double np=SmartDashboard::GetNumber("Straight PID P")/1000.;
	double ni=SmartDashboard::GetNumber("Straight PID I")/1000.;
	double nd=SmartDashboard::GetNumber("Straight PID D")/1000.;
	SetSetpoint(SmartDashboard::GetNumber("StraightGoal"));
	GetPIDController()->SetPID(np,ni,nd);
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
	return d;
}

void DriveStraight::UsePIDOutput(double output){
	if(output<0.11 && output >0.01)output=0.11;		//magic numbers. worked well in testing.
	if(output>-0.11 && output <-0.01)output=-0.11;
	chassis->arcadeDrive(output,0);
}

// Called once after isFinished returns true
void DriveStraight::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraight::Interrupted() {
	
}

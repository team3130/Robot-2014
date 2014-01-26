#include "DriveStraight.h"
#include "math.h"

DriveStraight::DriveStraight(double dist, double thresh, double timeToWait){
	Requires(chassis);
	goal=dist;
	distanceToGoal=goal;
	threshold=thresh;
	confirmTime=timeToWait;
}
// Called just before this Command runs the first time
void DriveStraight::Initialize() {
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
	//(4x|x|)/(4x^2+1)
	//This function has no mathematical significance; but because it tapers off near 0, it
	//is preferable to a purely proportional control. This function also has horizontal asymptotes
	//at both -1 and 1. This function rises more gradually than either a quadratic or
	//exponential control.
	//this function assumes distance is in meters.
	double x= distanceToGoal;
	double power = (4*x*fabs(x))/(4*x*x+1);
	if(power<-1)power=-1;
	if(power>1)power=1;
	chassis->straightDrive(power);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveStraight::IsFinished() {
	if(fabs(distanceToGoal)<threshold){
		timer.Start();
	}else{
		timer.Stop();
		timer.Reset();
	}
	if(timer.Get()>confirmTime)return true;
	else return false;
}

// Called once after isFinished returns true
void DriveStraight::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraight::Interrupted() {
	
}

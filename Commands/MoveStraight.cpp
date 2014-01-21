#include "MoveStraight.h"
#include "math.h"

MoveStraight::MoveStraight(float lDist, float rDist){
	Requires(chassis);
	lDistance=lDist;
	rDistance=rDist;
}
// Called just before this Command runs the first time
void MoveStraight::Initialize() {
	chassis->leftpc.reset();
	chassis->rightpc.reset();
	chassis->leftEncoder->Reset();
	chassis->rightEncoder->Reset();
	chassis->leftEncoder->Start();
	chassis->rightEncoder->Start();
	chassis->leftpc.setSetPoint(lDistance);
	chassis->rightpc.setSetPoint(rDistance);
	timer.Reset();
	timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void MoveStraight::Execute() {
	float setLeft=chassis->leftpc.update(chassis->leftEncoder->Get(),(long)timer.Get());
	float setRight=chassis->rightpc.update(chassis->rightEncoder->Get(),(long)timer.Get());
	chassis->tankDrive(setLeft,setRight);
}

// Make this return true when this Command no longer needs to run execute()
bool MoveStraight::IsFinished() {
	return fabs(chassis->leftEncoder->Get()-lDistance)<15 && fabs(chassis->leftEncoder->Get()-lDistance)<15;
}

// Called once after isFinished returns true
void MoveStraight::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveStraight::Interrupted() {
	
}

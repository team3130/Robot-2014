#include "MoveStraight.h"
#include "math.h"

MoveStraight::MoveStraight(){
	Requires(chassis);
}
// Called just before this Command runs the first time
void MoveStraight::Initialize() {
	chassis->leftEncoder->Reset();
	chassis->rightEncoder->Reset();
	chassis->leftEncoder->Start();
	chassis->rightEncoder->Start();
	timer.Reset();
	timer.Start();
	chassis->resetBias();
}

// Called repeatedly when this Command is scheduled to run
void MoveStraight::Execute() {
	double power = oi->leftJoystick->GetY()+oi->rightJoystick->GetY();
	if(power>0.1 || power<-0.1){
		chassis->straightDrive(power/2.0);
	}
	else{
		chassis->resetBias();
		chassis->tankDrive(0,0);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool MoveStraight::IsFinished() {
	return !oi->straightMode->Get();
}

// Called once after isFinished returns true
void MoveStraight::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveStraight::Interrupted() {
	
}

#include "MoveTo.h"
#include "Rotate.h"
#include "math.h"
MoveTo::MoveTo(double rotangle, double movedistance, double finalangle){
	Requires(chassis);
	finalAngle=finalangle;
	straightDist=movedistance;
	initRotate=rotangle;
	straight = 0;
	rotate = 0;
	rotate2 = 0;
	done=false;
}
double finalAngle;
	double straightDist;
	double initRotate;
// Called just before this Command runs the first time
void MoveTo::Initialize() {
	rotate=new Rotate(initRotate,2.5,1);
	rotate->Start();
}

// Called repeatedly when this Command is scheduled to run
void MoveTo::Execute() {
	if(rotate->IsFinished()){
		if(straight==0){
			chassis->gyro->Reset();
			straight=new DriveStraight(straightDist,Chassis::feetToEncoderUnits(.2),1);
			straight->Start();
		}else if(straight->IsFinished()){
			if(rotate2==0){
				double gyroDrift = chassis->gyro->Reset();	//the amount the robot has rotated while moving straight.
				rotate2=new Rotate(-gyroDrift,2.5,.4);
			}else if(rotate2->IsFinished()){
				done=true;
			}
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool MoveTo::IsFinished() {
	return done;
}

// Called once after isFinished returns true
void MoveTo::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveTo::Interrupted() {
}

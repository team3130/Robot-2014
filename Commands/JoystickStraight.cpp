#include "JoystickStraight.h"
#include "math.h"

JoystickStraight::JoystickStraight(){
	Requires(chassis);
}
// Called just before this Command runs the first time
void JoystickStraight::Initialize() {
	double ppd=Chassis::ENCODER_TOP_SPEED;	//# pulses per distance per second at maximum speed
	chassis->leftEncoder->SetDistancePerPulse(1.0/ppd);
	chassis->rightEncoder->SetDistancePerPulse(1.0/ppd);
	chassis->leftEncoder->SetPIDSourceParameter(PIDSource::kRate);
	chassis->rightEncoder->SetPIDSourceParameter(PIDSource::kRate);
	chassis->leftEncoder->Reset();
	chassis->rightEncoder->Reset();
	chassis->leftEncoder->Start();
	chassis->rightEncoder->Start();
	chassis->drive->SmartRobot();
}

// Called repeatedly when this Command is scheduled to run
void JoystickStraight::Execute() {
	double power = oi->rightJoystick->GetY();
	if(power>0.07 || power<-0.07){
		chassis->arcadeDrive(power, oi->leftJoystick->GetX());
	}
	else{
		// chassis->drive->updatePIDValues();
		chassis->tankDrive(0,0);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool JoystickStraight::IsFinished() {
	return !oi->straightMode->Get();
}

// Called once after isFinished returns true
void JoystickStraight::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void JoystickStraight::Interrupted() {
	
}

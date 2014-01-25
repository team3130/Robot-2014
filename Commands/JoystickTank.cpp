#include "JoystickTank.h"
#include "math.h"

JoystickTank::JoystickTank(): lrdifvc("Chassis LR Difference"){
	Requires(chassis);
	precisionMultiplier = 0.6666666666f;
	precisionLevel = 0;
	maxPrecisionLevel = 2;
	//SmartDashboard::PutNumber("JoystickTank: Joystick To Speed Multiplier",1.f);
	
}
// Called just before this Command runs the first time
void JoystickTank::Initialize() {
	lrdifvc.reset();
	chassis->leftEncoder->Reset();
	chassis->rightEncoder->Reset();
	chassis->leftEncoder->Start();
	chassis->rightEncoder->Start();
	lrdifvc.setSetPoint(0);
	PIDTimer.Reset();
	PIDTimer.Start();
}

// Called repeatedly when this Command is scheduled to run
void JoystickTank::Execute() {
	//deadzones
	float leftStick = oi->leftJoystick->GetY();
	float rightStick = oi->rightJoystick->GetY();
	SmartDashboard::PutNumber("Left Stick", leftStick);
	SmartDashboard::PutNumber("Right Stick", rightStick);
	if (fabs(leftStick)<.1f){
		leftStick = 0;
	}
	if (fabs(rightStick)<.1f){
		rightStick = 0;
	}
	//precision mode
	int leftPrecision = oi->leftPrecision->Get()?1:0;		//1 if button pressed, 0 otherwise.
	int rightPrecision = oi->rightPrecision->Get()?1:0;		//1 if button pressed, 0 otherwise.
	precisionLevel = leftPrecision+rightPrecision;
	float multiplier = pow(precisionMultiplier, precisionLevel);
	
	//calculate observed bias between the two motors
	float observedRightBias= chassis->rightEncoder->GetRate() - chassis->leftEncoder->GetRate(); 	//right encoder velocity - left encoder velocity
	//calculate average observed speed of both motors
	float speed = ((chassis->rightEncoder->GetRate() - chassis->leftEncoder->GetRate())/2);
	//divide observed bias by speed, because bias is directly proportional to speed.
	float observedBiasPerSpeed = observedRightBias/speed;
	//get a calculated correction value through PID.
	float correct=lrdifvc.update(observedBiasPerSpeed,(int)PIDTimer.Get());
	//because observed bias is directly proportional to speed, the correction bias must also
	//be directly proportional to speed. Dividing and multiplying by speed allows us a solution
	//that is independent of the speed of the robot. Correction bias amounts would otherwise
	//vary with the speed of the robot, and the PID controller would become unreliable. PID does
	//not itself well to the presence of multiple quickly-changing variables.
	correct*=speed;
	chassis->tankDrive(joystickToSpeed(leftStick*multiplier)+correct,	//correction to motor inputs.
			joystickToSpeed(rightStick*multiplier)-correct);
}
//convert joystick value to a speed (m/s)
float JoystickTank::joystickToSpeed(float in){
	return in * 1; //SmartDashboard::GetNumber("JoystickTank: Joystick To Speed Multiplier");
}
// Make this return true when this Command no longer needs to run execute()
bool JoystickTank::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void JoystickTank::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void JoystickTank::Interrupted() {
}

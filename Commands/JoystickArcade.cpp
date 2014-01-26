#include "JoystickArcade.h"
#include "math.h"

JoystickArcade::JoystickArcade(): lrdifvc("Chassis LR Difference"){
	Requires(chassis);
	precisionMultiplier = 0.6666666666f;
	precisionLevel = 0;
	maxPrecisionLevel = 2;
	//SmartDashboard::PutNumber("JoystickArcade: Joystick To Speed Multiplier",1.f);
	
}
// Called just before this Command runs the first time
void JoystickArcade::Initialize() {
	lrdifvc.reset();
	chassis->leftEncoder->Reset();
	chassis->rightEncoder->Reset();
	chassis->leftEncoder->Start();
	chassis->rightEncoder->Start();
	lrdifvc.setSetPoint(0);
	PIDTimer.Reset();
	PIDTimer.Start();
	dashboardSendTimer.Start();
}

// Called repeatedly when this Command is scheduled to run
void JoystickArcade::Execute() {
	//deadzones
	float leftStick = oi->leftJoystick->GetX();
	float rightStick = oi->rightJoystick->GetY();
	SmartDashboard::PutNumber("Left Stick", leftStick);
	SmartDashboard::PutNumber("Right Stick", rightStick);
	if (fabs(leftStick)<.15f){
		leftStick = 0;
	}
	if (fabs(rightStick)<.07f){
		rightStick = 0;
	}
	//precision mode
	int leftPrecision = oi->leftPrecision->Get()?1:0;		//1 if button pressed, 0 otherwise.
	int rightPrecision = oi->rightPrecision->Get()?1:0;		//1 if button pressed, 0 otherwise.
	precisionLevel = leftPrecision+rightPrecision;
	float multiplier = pow(precisionMultiplier, precisionLevel);
	if(leftStick==0){
		float rDirectionMultiplier = chassis->rightEncoder->GetDirection()?1:-1;
		float lDirectionMultiplier = chassis->leftEncoder->GetDirection()?1:-1;
		//calculate observed bias between the two motors
		float observedRightBias= chassis->rightEncoder->GetRate()*rDirectionMultiplier - chassis->leftEncoder->GetRate()*lDirectionMultiplier; 	//right encoder velocity - left encoder velocity
		//calculate average observed speed of both motors
		float speed = ((chassis->rightEncoder->GetRate()*rDirectionMultiplier - chassis->leftEncoder->GetRate()*lDirectionMultiplier)/2);
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
		//tank drive: control each motor independently. we are just going straight.
		chassis->tankDrive(joystickToSpeed(rightStick*multiplier)+correct,	//correction to motor inputs.
				joystickToSpeed(rightStick*multiplier)-correct);
		//send all values to smartdashboard
		if(dashboardSendTimer.Get()>3){	//every 20ms
			SmartDashboard::PutNumber("Observed Right Bias ", observedRightBias);
			SmartDashboard::PutNumber("Speed", speed);
			SmartDashboard::PutNumber("Observed Bias Per Speed", observedBiasPerSpeed);
			SmartDashboard::PutNumber("Correct", correct);
			SmartDashboard::PutNumber("Left Speed", chassis->leftEncoder->GetRate());
			SmartDashboard::PutNumber("Right Speed", chassis->leftEncoder->GetRate());
			dashboardSendTimer.Reset();
		}
	}else{	//don't use pid because we aren't going straight.
		lrdifvc.resetTime();	//so delta time isn't counted even when we aren't using pid.
		chassis->arcadeDrive(joystickToSpeed(rightStick*multiplier),
						joystickToSpeed(leftStick*multiplier));
	}
}
//convert joystick value to a speed (m/s)
float JoystickArcade::joystickToSpeed(float in){
	return in * 1; //SmartDashboard::GetNumber("JoystickArcade: Joystick To Speed Multiplier");
}
// Make this return true when this Command no longer needs to run execute()
bool JoystickArcade::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void JoystickArcade::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void JoystickArcade::Interrupted() {
}

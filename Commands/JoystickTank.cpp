/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty                                                  */
/*-------------------------------------------------------------------------*/
#include "JoystickTank.h"
#include "math.h"

JoystickTank::JoystickTank(const char* name) : CommandBase(name) {
	Requires(chassis);
	precisionMultiplier = 0.6666666666f;
	precisionLevel = 0;
}

// Called just before this Command runs the first time
void JoystickTank::Initialize() {
	chassis->DumbRobot();
}

// Called repeatedly when this Command is scheduled to run
void JoystickTank::Execute() {
//	if(oi->leftJoystick->GetRawButton(11))chassis->ShiftGear(true);
//	else chassis->ShiftGear(false);
	//deadzones
	float leftStick = oi->leftJoystick->GetY();
	float rightStick = oi->rightJoystick->GetY();
	SmartDashboard::PutNumber("DInput1", chassis->input1->Get());
	SmartDashboard::PutNumber("DInput2", chassis->input1->Get());
	if (fabs(leftStick)<.07f){
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

	chassis->tankDrive(leftStick*multiplier, rightStick*multiplier);
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

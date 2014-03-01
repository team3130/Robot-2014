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
	previousDirection=0;
}

// Called just before this Command runs the first time
void JoystickTank::Initialize() {
	chassis->DumbRobot();
}

// Called repeatedly when this Command is scheduled to run
void JoystickTank::Execute() {
	float leftStick = oi->leftJoystick->GetY();
	float rightStick = oi->rightJoystick->GetY();

	//deadzones
	if (fabs(leftStick)<DEAD_BAND && fabs(rightStick)<DEAD_BAND){
		chassis->ShiftGear(false);
		chassis->tankDrive(0,0);
		return;
	}
	
	//precision mode
	float multiplier = 1.0;	//how much precision each level gives us.
	if(oi->leftPrecision->Get()) multiplier *= 0.666;
	if(oi->rightPrecision->Get()) multiplier *= 0.666;
	if(multiplier<1.0){
		chassis->ShiftGear(false);
		chassis->tankDrive(leftStick*multiplier, rightStick*multiplier);
		return;
	}

	// Automatic transmission
	if(	fabs(leftStick)>FULL_SPEED &&
		fabs(rightStick)>FULL_SPEED &&
		leftStick*rightStick>0)
	{
		if(chassis->CanUseEncoders()){
			if(chassis->GetRate() >= RED_ZONE) {
				chassis->ShiftGear(true);
			}
		} else {
			// Dumb drive, upshift immediately
			chassis->ShiftGear(true);
		}
	} else if(
		(leftStick<DEAD_BAND && rightStick>-DEAD_BAND) ||
		(leftStick>-DEAD_BAND && rightStick<DEAD_BAND) ||
		previousDirection*(leftStick+rightStick) < 0
	)
	{
		chassis->ShiftGear(false);
	}
	previousDirection = leftStick + rightStick;
	chassis->tankDrive(leftStick, rightStick);
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

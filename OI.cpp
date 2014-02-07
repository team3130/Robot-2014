/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty                                                  */
/*-------------------------------------------------------------------------*/
#include "OI.h"
#include "Commands/JoystickStraight.h"
#include "Commands/JoystickTank.h"
#include "Commands/SpinIntake.h"
#include "Commands/Extendintake.h"
OI::OI() {
	leftJoystick = new Joystick(1);
	rightJoystick = new Joystick(2);
	gamepad= new Joystick(3);
	leftPrecision = new JoystickButton(leftJoystick, 1);
	rightPrecision = new JoystickButton(rightJoystick, 1);
	straightMode = new JoystickButton(rightJoystick, 2);
	intakeTrigger = new JoystickButton(gamepad, 3);
	extendTrigger = new JoystickButton(gamepad, 2);
	straightMode->WhenPressed(new JoystickStraight());
	intakeTrigger->WhenPressed(new SpinIntake());
	extendTrigger->WhenPressed(new ExtendIntake());
	//straightMode->WhenReleased(new JoystickTank());
}

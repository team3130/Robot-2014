/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty, James Li                                        */
/*-------------------------------------------------------------------------*/
#include "OI.h"
#include "Commands/JoystickStraight.h"
#include "Commands/JoystickTank.h"
#include "Commands/ShootCatapult.h"
#include "Commands/SpinIntake.h"
#include "Commands/DriveStraight.h"
#include "Commands/Rotate.h"
#include "Commands/DriveHighGear.h"

OI::OI() {
	leftJoystick  = new Joystick(1);
	rightJoystick = new Joystick(2);
	gamepad       = new Joystick(3);
	leftPrecision  = new JoystickButton(leftJoystick, 1);
	rightPrecision = new JoystickButton(rightJoystick, 1);
	straightMode   = new JoystickButton(rightJoystick, 2);
	shifterButton  = new JoystickButton(rightJoystick, B_HIGHGEAR);

	straightMode->WhenPressed(new JoystickStraight());
	shifterButton->WhenPressed(new DriveHighGear());
}

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
#include "Commands/DriveLowGear.h"
#include "Commands/WindCatapult.h"

OI::OI() {
	leftJoystick  = new Joystick(1);
	rightJoystick = new Joystick(2);
	gamepad       = new Joystick(3);
	leftPrecision  = new JoystickButton(leftJoystick, 1);
	rightPrecision = new JoystickButton(rightJoystick, 1);
	straightMode   = new JoystickButton(rightJoystick, 2);
	shiftUpButton1  = new JoystickButton(rightJoystick, B_HIGHGEAR1);
	shiftDnButton1  = new JoystickButton(leftJoystick, B_LOWGEAR1);
	shiftUpButton2  = new JoystickButton(rightJoystick, B_HIGHGEAR2);
	shiftDnButton2  = new JoystickButton(leftJoystick, B_LOWGEAR2);
	manualWinchControl = new JoystickButton(gamepad, 9);
	triggerShoot = new JoystickButton(gamepad,B_SHOOT);
	triggerShoot->WhenReleased(new WindCatapult("Teleop Rewind After Shot"));

	//triggerShoot->WhenPressed(new ShootCatapult("Shoot manual"));
	triggerShoot->WhenReleased(new WindCatapult("Tele Reload catapult"));
	straightMode->WhenPressed(new JoystickStraight("Straight manual"));
	shiftUpButton1->WhenPressed(new DriveHighGear("Shift up manual1"));
	shiftDnButton1->WhenPressed(new DriveLowGear("Shift down manual1"));
	shiftUpButton2->WhenPressed(new DriveHighGear("Shift up manual2"));
	shiftDnButton2->WhenPressed(new DriveLowGear("Shift down manual2"));
	
}

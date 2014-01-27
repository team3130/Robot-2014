/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty                                                  */
/*-------------------------------------------------------------------------*/
#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:

public:
	OI();
	Joystick* leftJoystick;
	Joystick* rightJoystick;
	Joystick* gamepad;
	JoystickButton* leftPrecision;
	JoystickButton* rightPrecision;
	JoystickButton* straightMode;
};

#endif

/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li                                                       */
/*-------------------------------------------------------------------------*/

#ifndef JOYSTICK_SHOOT_H
#define JOYSTICK_SHOOT_H

#include "../CommandBase.h"
#include "WPILib.h"

class JoystickShoot: public CommandBase {
public:
	DigitalInput** allInputs;
	JoystickShoot(const char* name);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

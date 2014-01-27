/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty                                                  */
/*-------------------------------------------------------------------------*/
#ifndef EXAMPLE_COMMAND_H
#define EXAMPLE_COMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class JoystickTank: public CommandBase {
private:
	float precisionMultiplier;	//how much precision each level gives us.
	int precisionLevel;			//level of precision we want. 0 is default
	int maxPrecisionLevel;		//maximum precision level.
	NaivePIDController lrdifvc;	//left right difference velocity controller.
	Timer PIDTimer;
	Timer dashboardSendTimer;
public:
	JoystickTank();
	float joystickToSpeed(float in);	//convert joystick value to a speed (m/s)
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

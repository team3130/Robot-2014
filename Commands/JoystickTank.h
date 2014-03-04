/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty                                                  */
/*-------------------------------------------------------------------------*/
#ifndef JOYSTICKTANK_H
#define JOYSTICKTANK_H

#include "../CommandBase.h"

static const float DEAD_BAND = 0.15;
static const float FULL_SPEED = 1.0;
static const float RED_ZONE = 90.0; // TODO find this experimentally (in/sec)

/**
 *
 *
 * @author ExampleAuthor
 */
class JoystickTank: public CommandBase {
private:
	float previousDirection;
public:
	JoystickTank(const char* name);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

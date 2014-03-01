/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty                                                  */
/*-------------------------------------------------------------------------*/
#ifndef JOYSTICKTANK_H
#define JOYSTICKTANK_H

#define DEAD_ZONE 0.08

#include "../CommandBase.h"

static const float DEAD_BAND = 0.08;
static const float FULL_SPEED = 0.92;
static const float RED_ZONE = 90.0; // TODO find this experimentally (in/sec)

/**
 *
 *
 * @author ExampleAuthor
 */
class JoystickTank: public CommandBase {
private:
<<<<<<< HEAD
//	static const float DEAD_ZONE = 0.08;
	static const float FULL_SPEED = 0.92;
	static const float RED_ZONE = 10.0; // TODO find this experimentally (ft/sec)
=======
>>>>>>> origin/master
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

/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li, Kevin Bi                                             */
/*-------------------------------------------------------------------------*/

#ifndef SHOOT_CATAPULT_H
#define SHOOT_CATAPULT_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShootCatapult: public CommandBase {
private:
	//bool Finished;
	//Timer to let the robot wait
	Timer timer;
	//Time the robot should wait after deactivating Solenoids
	//Undetermined value #UNDETERMINED
	static const double WaitTime = 500;
	bool IntakeSafe;
public:
	ShootCatapult();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

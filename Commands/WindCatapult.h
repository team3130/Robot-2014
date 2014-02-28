/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li, Kevin Bi                                             */
/*-------------------------------------------------------------------------*/

#ifndef WIND_CATAPULT_H
#define WIND_CATAPULT_H

#include "../CommandBase.h"
#include "WPILib.h"

class WindCatapult: public CommandBase {
private:
	bool done;
	int state;
	//Timer to let the robot wait
	Timer timer;
	//Time the robot should wait after deactivating Solenoids
	//Undetermined value #UNDETERMINED
	bool beginWaiting;
	double WaitTime;
public:
	WindCatapult(const char* name);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
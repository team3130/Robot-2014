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
	bool done;
	int state;
	Timer timer;
	bool canIShoot;
public:
	ShootCatapult(const char* name);
	void GrantPermission(bool ucan=true){canIShoot=ucan;}
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

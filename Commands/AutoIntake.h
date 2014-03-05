/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li                                                       */
/*-------------------------------------------------------------------------*/

#ifndef AUTO_INTAKE_H
#define AUTO_INTAKE_H

#include "../CommandBase.h"
#include "WPILib.h"

class AutoIntake: public CommandBase {
public:
	Timer loadTimer;
	bool done;
	AutoIntake();
	int GetPhase();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li                                                       */
/*-------------------------------------------------------------------------*/

#ifndef CHANGE_CATAPULT_END_H
#define CHANGE_CATAPULT_END_H

#include "../CommandBase.h"
#include "WPILIB.h"

class ChangeCatapultEnd: public CommandBase {
private:
	double timeSpan;
	double endPosition;
public:
	ChangeCatapultEnd();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

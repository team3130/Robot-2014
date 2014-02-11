/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Kevin Bi, James Li                                             */
/*-------------------------------------------------------------------------*/

#ifndef MOVE_CATAPULT_H
#define MOVE_CATAPULT_H

#include "../CommandBase.h"
#include "WPILIB.h"

class MoveCatapult: public CommandBase {
private:
	double timeLapse;
public:
	MoveCatapult();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

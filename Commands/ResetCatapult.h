/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Kevin Bi, James Li                                             */
/*-------------------------------------------------------------------------*/

#ifndef RESET_CATAPULT_H
#define RESET_CATAPULT_H

#include "../CommandBase.h"


class ResetCatapult: public CommandBase {
public:
	ResetCatapult();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
private:
	//Determines "phase"
	int CurAction;
	const int WINDING = 0;
	const int PINCHING = 1; 
	const int UNWINDING = 2;
	const int FINISHED = 3;
	//Undetermined value
	double ResetTime = 3;
	//Undetermined value
	double UnwindAmount = 0;
	//Undetermine value
	double UnwindTime = 0;
};

#endif

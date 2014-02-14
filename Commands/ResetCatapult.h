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
	static const int WINDING = 0;
	static const int PINCHING = 1;
	static const int UNWINDING = 2; 
	static const int FINISHED = 3; 
	//Undetermined value
	static const double WindSpeed = 0;  
	//Undetermined value
	static const double UnwindAmount = 0;
	//Undetermine value
	static const double UnwindSpeed = 0;
};

#endif

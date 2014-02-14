/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: <Kevin Bi>                                                     */
/*-------------------------------------------------------------------------*/

#ifndef SET_STOP_LOB_H
#define SET_STOP_LOB_H

#include "../CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class SetStopLob: public CommandBase {
private:
	//Undetermined value 
	static const double Position = 0;
public:
	SetStopLob();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

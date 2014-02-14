/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: <Kevin Bi>                                                     */
/*-------------------------------------------------------------------------*/

#ifndef SET_STOP_SHOOT_H
#define SET_STOP_SHOOT_H

#include "../CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class SetStobShoot: public CommandBase {
public:
	SetStobShoot();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

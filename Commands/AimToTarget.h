/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty                                                  */
/*-------------------------------------------------------------------------*/
#ifndef ATT_COMMAND_H
#define ATT_COMMAND_H

#include "../CommandBase.h"

/**
 *
 * This command assumes the robot to start from rest,
 * and is primarily meant to take place during autonomous.
 * Aim to the closest target.
 */
class AimToTarget: public CommandBase {
public:
	AimToTarget();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

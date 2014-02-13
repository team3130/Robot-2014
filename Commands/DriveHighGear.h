/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Mikhail Kyraha                                                 */
/*-------------------------------------------------------------------------*/
#ifndef DRIVEHIGHGEAR_H
#define DRIVEHIGHGEAR_H

#include "../CommandBase.h"

/**
 *
 *
 */
class DriveHighGear: public CommandBase {
public:
	DriveHighGear();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

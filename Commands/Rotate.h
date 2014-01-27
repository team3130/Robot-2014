/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty                                                  */
/*-------------------------------------------------------------------------*/
#ifndef ROTATE_H
#define ROTATE_H

#include "../CommandBase.h"

/**
 * @author Ashwin
 * 
 * The Rotate command uses the gyroscope to rotate the
 * robot by a specific angle. We should calculate angles
 * in degrees.
 */
class Rotate: public CommandBase {
public:
	Rotate();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

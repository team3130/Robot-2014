/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty                                                  */
/*-------------------------------------------------------------------------*/
#ifndef MOVE_STRAIGHT_H
#define MOVE_STRAIGHT_H

#include "../CommandBase.h"
#include "WPILib.h"

/**
 * @author Ashwin
 * This class uses the encoders (and maybe accelerometer or vision)
 * to move straight--either forward or backward--by a specific
 * distance.
 */
class DriveStraight: public CommandBase {
private:
	Timer timer;
	double goal;
	double distanceToGoal;
	double threshold;
	double confirmTime;
public:
	DriveStraight(double dist, double thresh, double timeToWait);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty, Mikhail Kyraha                                  */
/*-------------------------------------------------------------------------*/

#ifndef ROTATE_H
#define ROTATE_H

#include "../CommandBase.h"
#include "WPILib.h"
#include "../Subsystems/Chassis.h"

/**
 * @author Ashwin
 * This class uses the gyro (and maybe accelerometer or vision)
 * to turn the bot -- either right or left -- by a specific angle.
 */
class Rotate: public PIDCommand{
private:
	Timer timer;
	double goal;
	double threshold;
	double confirmTime;
	bool isConfirming;
public:
	Rotate();
	virtual void SetGoal(double dist, double thresh, double timeToWait);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	virtual double ReturnPIDInput();
	virtual void UsePIDOutput(double output);
};

#endif

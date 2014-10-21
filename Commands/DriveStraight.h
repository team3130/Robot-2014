/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty                                                  */
/*-------------------------------------------------------------------------*/
#ifndef DRIVE_STRAIGHT_H
#define DRIVE_STRAIGHT_H

#include "../CommandBase.h"
#include "WPILib.h"
#include "../Subsystems/Chassis.h"

/**
 * @author Ashwin
 * This class uses the encoders (and maybe accelerometer or vision)
 * to move straight--either forward or backward--by a specific
 * distance.
 */
class DriveStraight: public PIDCommand{
private:
	static constexpr double driftK = 1.0/180.0;
	Timer timer;
	double speed;
	double goal;
	double threshold;
	double confirmTime;
	double dumbDriveTime;
	double keepAngle;
	bool isConfirming;
	Chassis* chassis;	//from commandbase. we aren't a subclass of it b/c of deadly diamond of death
public:
	DriveStraight(const char *name);
	void SetGoal(double dist, double thresh=0, double timeToWait=0, double ispeed=1);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	virtual double ReturnPIDInput();
	virtual void UsePIDOutput(double output);
};

#endif

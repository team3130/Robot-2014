/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Mikhail Kyraha                                                 */
/*-------------------------------------------------------------------------*/

#ifndef ROTATE_H
#define ROTATE_H

#include "../CommandBase.h"
#include "WPILib.h"
#include "../Subsystems/Chassis.h"

/**
 * @author Ashwin
 * This class uses the encoders (and maybe accelerometer or vision)
 * to move straight--either forward or backward--by a specific
 * distance.
 */
<<<<<<< HEAD
class Rotate: public PIDCommand{
private:
	Timer timer;
	double goal;
	double distanceToGoal;
	double threshold;
	double confirmTime;
	PIDController* controller;
	Chassis* chassis;	//from commandbase. we aren't a subclass of it b/c of deadly diamond of death
public:
	Rotate(double dist, double thresh, double timeToWait, double p, double i, double d);
<<<<<<< HEAD
	Rotate(double dist, double thresh, double timeToWait);
=======
	Rotate();
=======
class Rotate : public PIDCommand {
public:
	Rotate(double angle, double p, double i, double d);
>>>>>>> 47bea4b9c9d7b12b7e1199060397fac8ff3aacdd
>>>>>>> parent of 8f46f47... functional and quick PID for position/rotation
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	virtual double ReturnPIDInput();
	virtual void UsePIDOutput(double output);
};

#endif

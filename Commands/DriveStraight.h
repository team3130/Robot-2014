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
	Timer timer;
	double goal;
	double distanceToGoal;
	double threshold;
	double confirmTime;
	Chassis* chassis;	//from commandbase. we aren't a subclass of it b/c of deadly diamond of death
public:
	DriveStraight(double dist, double thresh, double timeToWait, double p, double i, double d);
	DriveStraight();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	virtual double ReturnPIDInput();
	virtual void UsePIDOutput(double output);
};

#endif

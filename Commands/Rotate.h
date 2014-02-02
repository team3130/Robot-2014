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
	Rotate();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	virtual double ReturnPIDInput();
	virtual void UsePIDOutput(double output);
};

#endif

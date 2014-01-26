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

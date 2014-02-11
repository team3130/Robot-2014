#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H

#include "Commands/CommandGroup.h"
#include "DistanceTracking.h"
#include "DriveStraight.h"
#include "ResetCatapult.h"


class Autonomous: public CommandGroup {
private:
	//DistanceTracking* distanceTrack; //not actually a command
	DriveStraight* driveStraight;
	ResetCatapult* reset;
public:
	Autonomous();
	~Autonomous();
	virtual void Initialize();
};

#endif

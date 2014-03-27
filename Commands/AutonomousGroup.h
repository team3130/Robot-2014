#ifndef AUTONOMOUSGROUP_H
#define AUTONOMOUSGROUP_H

#include "../Robot.h"
#include "Commands/CommandGroup.h"
#include "DriveStraight.h"
#include "WaitForHot.h"
#include "ShootCatapult.h"
#include "WindCatapult.h"
#include "AccumulateCatapult.h"

/**
 *
 *
 * @author Nick
 */
class AutonomousGroup: public CommandGroup {
private:
	WindCatapult* loader;
	DriveStraight* driveStraight1;
	WaitForHot* waitForHot;
	ShootCatapult* shoot;
	DriveStraight* driveStraight2;
	Timer hotGoalTimer;
	AccumulateCatapult* accum;
	AccumulateCatapult* accum2;
public:	
	AutonomousGroup();
	~AutonomousGroup();
	void Initialize();
	void Execute();
	void End();
	void Interrupted();
};

#endif

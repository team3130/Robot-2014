#ifndef AUTONOMOUSGROUP_H
#define AUTONOMOUSGROUP_H

#include "Commands/CommandGroup.h"
#include "DriveStraight.h"
#include "WaitForHot.h"
#include "ShootCatapult.h"
#include "DriveStraightGyro.h"
#include "IdleIntake.h"

/**
 *
 *
 * @author Nick
 */
class AutonomousGroup: public CommandGroup {
private:
	IdleIntake* idle;
	DriveStraightGyro* driveStraight1;
	WaitForHot* waitForHot;
	ShootCatapult* shoot;
	DriveStraightGyro* driveStraight2;
public:	
	AutonomousGroup();
	~AutonomousGroup();
	virtual void Initialize();
};

#endif

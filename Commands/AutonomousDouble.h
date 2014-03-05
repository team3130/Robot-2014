#ifndef AUTONOMOUSDOUBLE_H
#define AUTONOMOUSDOUBLE_H

#include "../Robot.h"
#include "Commands/CommandGroup.h"
#include "DriveStraight.h"
#include "WaitForHot.h"
#include "ShootCatapult.h"
#include "WindCatapult.h"
#include "AccumulateCatapult.h"
#include "AutoIntake.h"

/**
 *
 *
 * @author Nick
 */
class AutonomousDouble: public CommandGroup {
private:
	DriveStraight* driveToBall;
	ShootCatapult* shoot1;
	ShootCatapult* shoot2;
	DriveStraight* driveZone;
	AccumulateCatapult* accum;
	AutoIntake* getBall;
public:	
	AutonomousDouble();
	~AutonomousDouble();
	void Initialize();
	void Execute();
	void End();
};

#endif

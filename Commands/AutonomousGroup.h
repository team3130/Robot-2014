#ifndef AUTONOMOUSGROUP_H
#define AUTONOMOUSGROUP_H

#include "../Robot.h"
#include "Commands/CommandGroup.h"
#include "DriveStraight.h"
#include "WaitForHot.h"
#include "ShootCatapult.h"
#include "IdleIntake.h"

/**
 *
 *
 * @author Nick
 */
class AutonomousGroup: public CommandGroup {
private:
	// DigitalOutput* pLEDRelay; todo
	IdleIntake* idle;
	DriveStraight* driveStraight1;
	WaitForHot* waitForHot;
	ShootCatapult* shoot;
	DriveStraight* driveStraight2;
public:	
	AutonomousGroup();
	~AutonomousGroup();
	virtual void Initialize();
	virtual void End();
};

#endif

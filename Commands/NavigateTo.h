#ifndef NAVIGATETO_H
#define NAVIGATETO_H

#include "Commands/CommandGroup.h"
#include "Rotate.h"
#include "DriveStraight.h"

/**
 *
 *
 * @author U0172740
 */
class NavigateTo: public CommandGroup {
private:
	Rotate* rotateFirst;
	DriveStraight* driveStraight;
	Rotate* rotateSecond;
	double firstRotateAngle;
	double moveDist;
	double finalRotateAngle;
	
public:	
	NavigateTo(const char *name);
	~NavigateTo();
	void SetGoalCartesian(double cartX, double cartY, double finalRotation);
	void SetGoalPolar(double rotate, double distance, double finalRotation);
	virtual void Initialize();
};

#endif

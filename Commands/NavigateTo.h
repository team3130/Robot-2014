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
public:	
	NavigateTo();
	~NavigateTo();
};

#endif

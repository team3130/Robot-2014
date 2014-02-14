#ifndef NAVIGATETO_H
#define NAVIGATETO_H

#include "Commands/CommandGroup.h"
#include "ShootCatapult.h"
#include "ResetCatapult.h"
#include "WindCatapult.h"

class ShootCycle: public CommandGroup {
private:
	ShootCatapult* shoot;
	ResetCatapult* reset;
	WindCatapult* wind;
	
public:	
	ShootCycle();
	~ShootCycle();
	virtual void Initialize();
};

#endif

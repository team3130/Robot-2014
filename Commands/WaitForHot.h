#ifndef WAITFORHOT_H
#define WAITFORHOT_H
#include "DistanceTracking.h"
#include "../Robot.h"

/**
 *
 *
 * @author Mike
 */
class WaitForHot: public CommandBase {
public:
	WaitForHot(const char* name);
	~WaitForHot();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	DistanceTracking* distanceTracking;
	int hotCount;
	int hotIterate;
	int hotMethod; // 0 = aimed, 1 = distance
	Timer timer;
	
	static bool sm_bIsHot;
	static bool sm_bInitialCheck;
};

#endif

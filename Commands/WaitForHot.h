#ifndef WAITFORHOT_H
#define WAITFORHOT_H
#include "DistanceTracking.h"
#include "../CommandBase.h"
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
	int hotScans;
	int hotConfirms;
	double initWait;
	int hotCount;
	int hotIterate;
	int hotMethod; // 0 = aimed, 1 = distance, 2 = shape matching
	Timer timer;
	
	static bool sm_bIsHot;
};

#endif

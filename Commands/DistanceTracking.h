#ifndef DISTANCE_TRACKING_H
#define DISTANCE_TRACKING_H

#include "../CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class DistanceTracking: public CommandBase {
public:
	DistanceTracking();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	virtual double findTriangleHeight(const double & dSideA, const double & dSideB, const double & dTotalBase);
};

#endif

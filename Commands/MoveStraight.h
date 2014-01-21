#ifndef MOVE_STRAIGHT_H
#define MOVE_STRAIGHT_H

#include "../CommandBase.h"
#include "WPILib.h"

/**
 * @author Ashwin
 * This class uses the encoders (and maybe accelerometer or vision)
 * to move straight--either forward or backward--by a specific
 * distance. For the sake of physics calculations, we should use
 * meters.
 */
class MoveStraight: public CommandBase {
private:
	Timer timer;
	float lDistance;
	float rDistance;
public:
	MoveStraight(float lDist, float rDist);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

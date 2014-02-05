#ifndef MOVETO_COMMAND_H
#define MOVETO_COMMAND_H

#include "../CommandBase.h"

/**
 *
 * This command assumes the robot to start from rest,
 * and is primarily meant to take place during autonomous.
 * Aim to the closest target.
 */
class MoveTo: public CommandBase {
public:
	MoveTo(double rotangle, double movedistance, double finalangle);
	double finalAngle;
	double straightDist;
	double initRotate;
	Command* straight;
	Command* rotate;
	Command* rotate2;
	bool done;
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

#ifndef ATT_COMMAND_H
#define ATT_COMMAND_H

#include "../CommandBase.h"

/**
 *
 * This command assumes the robot to start from rest,
 * and is primarily meant to take place during autonomous.
 * Aim to the closest target.
 */
class AimToTarget: public CommandBase {
public:
	AimToTarget();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

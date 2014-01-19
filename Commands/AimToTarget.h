#ifndef ATT_COMMAND_H
#define ATT_COMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
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

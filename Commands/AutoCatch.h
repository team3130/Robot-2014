#ifndef AUTOCATCH_COMMAND_H
#define AUTOCATCH_COMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class AutoCatch: public CommandBase {
public:
	AutoCatch();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

#ifndef LOGSHOOTER_H
#define LOGSHOOTER_H

#include "../CommandBase.h"
#include "../Logger/Logger.h"

/**
 *
 *
 * @author 3130
 */
class LogShooter: public CommandBase {
	Logger* log;
public:
	LogShooter();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

#ifndef LOGCHASSIS_H
#define LOGCHASSIS_H

#include "../CommandBase.h"
#include "../Logger/Logger.h"

/**
 *
 *
 * @author 3130
 */
class LogChassis: public CommandBase {
	Logger* m_logger;
public:
	LogChassis(const char* name = "");
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

#ifndef EXAMPLE_COMMAND_H
#define EXAMPLE_COMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class JoystickTank: public CommandBase {
private:
	float precisionMultiplier;	//how much precision each level gives us.
	int precisionLevel;			//level of precision we want. 0 is default
public:
	JoystickTank();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

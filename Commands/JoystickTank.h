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
	int maxPrecisionLevel;		//maximum precision level.
	NaivePIDController lrdifvc;	//left right difference velocity controller.
	Timer PIDTimer;
public:
	JoystickTank();
	float joystickToSpeed(float in);	//convert joystick value to a speed (m/s)
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

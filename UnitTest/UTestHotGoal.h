#ifndef UTESTHOTGOAL_H
#define UTESTHOTGOAL_H

#include "WPILib.h"
#include "Commands/CommandGroup.h"
#include "../Commands/WaitForHot.h"

/**
 *
 *
 * @author M.Kyraha
 */
class UTestHotGoal: public CommandGroup {
private:
	WaitForHot* waitForHot;
	Timer hotGoalTimer;
public:	
	UTestHotGoal();
	~UTestHotGoal();
	void Initialize();
	void Execute();
};

#endif

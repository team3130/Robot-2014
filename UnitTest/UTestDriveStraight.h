#ifndef UTESTDRIVESTRAIGHT_H
#define UTESTDRIVESTRAIGHT_H

#include "Commands/CommandGroup.h"
#include "../Commands/DriveStraight.h"

/**
 *
 *
 * @author M.Kyraha
 */
class UTestDriveStraight: public CommandGroup {
private:
	DriveStraight* m_command;
public:	
	UTestDriveStraight();
	void Initialize();
};

#endif

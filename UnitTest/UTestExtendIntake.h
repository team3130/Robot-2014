#ifndef UTESTEXTENDINTAKE_H
#define UTESTEXTENDINTAKE_H

#include "Commands/CommandGroup.h"
#include "../Commands/ExtendIntake.h"

/**
 *
 *
 * @author J. Li
 */
class UTestExtendIntake: public CommandGroup {
private:
	ExtendIntake* m_command;
public:	
	UTestExtendIntake();
	void Initialize();
};

#endif

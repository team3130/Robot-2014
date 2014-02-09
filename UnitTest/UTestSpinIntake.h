#ifndef UTESTSPININTAKE_H
#define UTESTSPININTAKE_H

#include "Commands/CommandGroup.h"
#include "../Commands/SpinIntake.h"

/**
 *
 *
 * @author J. Li
 */
class UTestSpinIntake: public CommandGroup {
private:
	SpinIntake* m_command;
public:	
	UTestSpinIntake();
	void Initialize();
};

#endif

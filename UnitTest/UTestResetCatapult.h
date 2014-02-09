#ifndef UTESTRESETCATAPULT_H
#define UTESTRESETCATAPULT_H

#include "Commands/CommandGroup.h"
#include "../Commands/ResetCatapult.h"

/**
 *
 *
 * @author K. Bi, J. Li
 */
class UTestResetCatapult: public CommandGroup {
private:
	ResetCatapult* m_command;
public:	
	UTestResetCatapult();
	void Initialize();
};

#endif

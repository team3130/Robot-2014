#ifndef UTESTCHANGECATAPULTEND_H
#define UTESTCHANGECATAPULTEND_H

#include "Commands/CommandGroup.h"
#include "../Commands/ChangeCatapultEnd.h"

/**
 *
 *
 * @author J. Li
 */
class UTestChangeCatapultEnd: public CommandGroup {
private:
	ChangeCatapultEnd* m_command;
public:	
	UTestChangeCatapultEnd();
	void Initialize();
};

#endif

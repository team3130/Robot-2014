#ifndef UTESTMOVECATAPULT_H
#define UTESTMOVECATAPULT_H

#include "Commands/CommandGroup.h"
#include "../Commands/MoveCatapult.h"

/**
 *
 *
 * @author J. Li
 */
class UTestMoveCatapult: public CommandGroup {
private:
	MoveCatapult* m_command;
public:	
	UTestMoveCatapult();
	void Initialize();
};

#endif

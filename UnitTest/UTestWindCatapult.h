#ifndef UTESTMOVECATAPULT_H
#define UTESTMOVECATAPULT_H

#include "Commands/CommandGroup.h"
#include "../Commands/WindCatapult.h"

/**
 *
 *
 * @author J. Li
 */
class UTestWindCatapult: public CommandGroup {
private:
	WindCatapult* m_command;
public:	
	UTestWindCatapult();
	void Initialize();
};

#endif

#ifndef UTESTSHOOTCATAPULT_H
#define UTESTSHOOTCATAPULT_H

#include "Commands/CommandGroup.h"
#include "../Commands/ShootCatapult.h"

/**
 *
 *
 * @author J. Li
 */
class UTestShootCatapult: public CommandGroup {
private:
	ShootCatapult* m_command;
public:	
	UTestShootCatapult();
	void Initialize();
};

#endif

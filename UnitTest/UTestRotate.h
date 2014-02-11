#ifndef UTESTROTATE_H
#define UTESTROTATE_H

#include "Commands/CommandGroup.h"
#include "../Commands/Rotate.h"

/**
 *
 *
 * @author M.Kyraha
 */
class UTestRotate: public CommandGroup {
private:
	Rotate* m_command;
public:	
	UTestRotate();
	void Initialize();
};

#endif

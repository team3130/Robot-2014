#ifndef UTESTNAVIGATETO_H
#define UTESTNAVIGATETO_H

#include "Commands/CommandGroup.h"
#include "../Commands/NavigateTo.h"

/**
 *
 *
 * @author M.Kyraha
 */
class UTestNavigateTo: public CommandGroup {
private:
	NavigateTo* m_command;
public:	
	UTestNavigateTo();
	void Initialize();
};

#endif

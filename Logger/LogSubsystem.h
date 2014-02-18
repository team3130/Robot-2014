/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Matthew Ickstadt                                               */
/*-------------------------------------------------------------------------*/

#ifndef __LOGSUBSYSTEM_H__
#define __LOGSUBSYSTEM_H__

#include "WPILib.h"

class Command;

class LogSubsystem: public Subsystem {
	Command* m_logcommand;
public:
	// The LogCommand runs periodically to log the state of a subsystem.
	// if you want something to only be logged when it changes, add it to a
	// command that runs when that change occurs using WhenPressed(), etc.
	virtual void InitLogCommand();
	void SetLogCommand(Command*);
	
	LogSubsystem(const char* name) :
		Subsystem(name) {
		InitLogCommand();
	}

};

#endif

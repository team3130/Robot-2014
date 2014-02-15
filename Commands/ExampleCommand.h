/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: <INSERT AUTHOR(S) OF CODE>                                     */
/*-------------------------------------------------------------------------*/

#ifndef EXAMPLE_COMMAND_H2
#define EXAMPLE_COMMAND_H2
#include "../CommandBase.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class ExampleCommand: public CommandBase {
public:
	ExampleCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: <INSERT AUTHOR(S) OF CODE>                                     */
/*-------------------------------------------------------------------------*/

<<<<<<< HEAD
#ifndef EXAMPLE_COMMAND_H2
#define EXAMPLE_COMMAND_H2
=======
#ifndef EXAMPLE_COMMAND_H
#define EXAMPLE_COMMAND_H
>>>>>>> 955395e11745ae8e33374fdb8bc497ed9c89537d
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

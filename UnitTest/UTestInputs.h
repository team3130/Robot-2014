/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Mikhail Kyraha                                                 */
/*-------------------------------------------------------------------------*/
#ifndef UTEST_INPUTS_H
#define UTEST_INPUTS_H

#include <vector>
#include "WPILib.h"

class UTestInputs: public Command
{
public:
	std::vector<DigitalInput*> m_inputs;
	UTestInputs();
	~UTestInputs();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

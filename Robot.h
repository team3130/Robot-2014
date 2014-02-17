/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Mikhail Kyraha, Ashwin Chetty                                  */
/*-------------------------------------------------------------------------*/
#ifndef MAINROBOT_H
#define MAINROBOT_H

#include "WPILib.h"
#include "Robotmap.h"
#include "Commands/Command.h"
#include "UnitTest/UnitTest.h"
#include "CommandBase.h"

class Robot {
public:
	static Preferences* preferences;
	static UnitTest*    unitTest;
};

#endif

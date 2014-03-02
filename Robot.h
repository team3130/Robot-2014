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

class Robot {
public:
	static UnitTest*    unitTest;
	static const unsigned int LeftEncoderPPR=0;
	static const unsigned int RightEncoderPPR=0;
	// Theoretical max speed of the bot on low gear in inches per second
	// Has to be unreachable closest amount.
	static const double LowGearTopSpeed=150;
	static const double StopperEncoderPPI=114.53;
};

#endif

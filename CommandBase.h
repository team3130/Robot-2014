/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty                                                  */
/*-------------------------------------------------------------------------*/
#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include "math.h"
#include "Commands/Command.h"
#include "Subsystems/Chassis.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/Intake.h"
#include "UnitTest/UnitTest.h"
#include "OI.h"


/**
 * The base for all commands. All atomic commands should subclass CommandBase.
 * CommandBase stores creates and stores each control system. To access a
 * subsystem elsewhere in your code in your code use CommandBase.examplesubsystem
 */
class CommandBase: public Command {
public:
	CommandBase(const char *name);
	CommandBase();
	static void init();
	// Create a single static instance of all of your subsystems
	//static ExampleSubsystem *examplesubsystem;
	static Compressor* compressor;
	static Chassis* chassis;
	static Shooter* shooter;
	static Intake* intake;
	static OI *oi;
	
	static UnitTest* unitTest;
};

static inline double ConstrainAngle(double x){
    x = fmod(x + 180,360);
    if (x < 0) x += 360;
    return x - 180;
}

#endif

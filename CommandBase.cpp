/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty                                                  */
/*-------------------------------------------------------------------------*/
#include "CommandBase.h"
#include "Commands/Scheduler.h"
#include "Subsystems/Chassis.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/Intake.h"
#include "Robotmap.h"
#include "UnitTest/UnitTest.h"

CommandBase::CommandBase(const char *name) : Command(name) {
}
CommandBase::CommandBase() : Command() {
}

// Initialize a single static instance of all of your subsystems to NULL
Compressor* CommandBase::compressor = NULL;
Chassis* CommandBase::chassis = NULL;
Shooter* CommandBase::shooter = NULL;
StopperWinch* CommandBase::stopper = NULL;
Intake* CommandBase::intake = NULL;
OI* CommandBase::oi = NULL;
Logger* CommandBase::logger = NULL;

void CommandBase::init() {
    // Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	//examplesubsystem = new ExampleSubsystem();
	compressor = new Compressor(C_PRESSURE_SWITCH, C_COMPRESSOR_RELAY);
	shooter = new Shooter(C_WINCHMOTOR1, C_SHOOTERSOLENOID1, C_SHOOTERSOLENOID2);
	stopper = new StopperWinch();
	intake = new Intake();
	chassis = new Chassis();
	oi = new OI();
	compressor->Start();
	logger = new Logger();
}

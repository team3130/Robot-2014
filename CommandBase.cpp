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
Chassis* CommandBase::chassis = NULL;
Shooter* CommandBase::shooter = NULL;
Intake* CommandBase::intake = NULL;
OI* CommandBase::oi = NULL;
UnitTest* CommandBase::unitTest = NULL;

void CommandBase::init() {
    // Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	//examplesubsystem = new ExampleSubsystem();
	shooter = new Shooter(C_WINCHMOTOR1, C_SHOOTERSOLENOID1);
	intake = new Intake(C_INTAKEMOTOR1, C_EXTENDSOLENOID1);
	chassis = new Chassis();
	oi = new OI();
	unitTest = new UnitTest();
}

/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li                                                       */
/*-------------------------------------------------------------------------*/

#include "Autonomous.h"

Autonomous::Autonomous() {
	//distanceTrack = new DistanceTracking(); //not actually a command
	driveStraight = new DriveStraight("Drive Straight Test");
	reset = new ResetCatapult();
	//AddSequential(distanceTrack); //not actually a command
	AddSequential(driveStraight);
	AddSequential(reset);
}

Autonomous::~Autonomous()
{
	//delete distanceTrack; //not actually a command
	delete driveStraight;
	delete reset;
}

// Called just before this Command runs the first time
void Autonomous::Initialize() {
	
}

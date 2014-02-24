/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty, Mikhail Kyraha                                  */
/*-------------------------------------------------------------------------*/

#include "NavigateTo.h"
#include "math.h"

NavigateTo::NavigateTo(const char *name) : CommandGroup(name) {
	rotateFirst = new Rotate("NavFirstRotate");
	driveStraight = new DriveStraight("NavStraight");
	rotateSecond = new Rotate("NavSecondRotate");
	firstRotateAngle=0;
	finalRotateAngle=0;
	moveDist=0;
	AddSequential(rotateFirst);
	AddSequential(driveStraight);
	AddSequential(rotateSecond);
}

NavigateTo::~NavigateTo() {
	delete rotateFirst;
	delete driveStraight;
	delete rotateSecond;
}

void NavigateTo::Initialize()
{
	static double cooldown = 0;
	static double threshold = 4;
	double totalTurn = fabs(ConstrainAngle(firstRotateAngle))+fabs(ConstrainAngle(finalRotateAngle));
	if(totalTurn<fabs(totalTurn-360)) {
		rotateFirst->SetGoal(firstRotateAngle,threshold,cooldown);
		driveStraight->SetGoal(moveDist,1.0,0.25);
		rotateSecond->SetGoal(finalRotateAngle,2,1, false);
	}
	else {
		// Rotate will renormalize the angles
		rotateFirst->SetGoal(firstRotateAngle-180,threshold,cooldown);
		driveStraight->SetGoal(-moveDist,1.0,0.25);
		rotateSecond->SetGoal(finalRotateAngle-180,2,1, false);
		
	}
}
/*
 * @param cartX offset from North axis, in inches. Positive is to the right
 * @param cartY offset toward the North, in inches.
 * @finalRotation the new North relative to initial North.
 */
void NavigateTo::SetGoalCartesian(double cartX, double cartY, double finalRotation){
	// It's X over Y because the angle is from the North
	firstRotateAngle = 360*atan2(cartX, cartY)/(2*M_PI);	
	moveDist = sqrt(cartX*cartX + cartY*cartY);
	SetGoalPolar(firstRotateAngle, moveDist, finalRotation);
}
/*
 * @rotate rotation angle
 * @distance distance in inches
 */
void NavigateTo::SetGoalPolar(double rotate, double distance, double finalRotation){
	firstRotateAngle = rotate;
	finalRotateAngle = finalRotation - firstRotateAngle;
	moveDist = distance;
}

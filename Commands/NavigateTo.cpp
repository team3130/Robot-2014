#include "NavigateTo.h"
#include "math.h"
NavigateTo::NavigateTo() {
        // Add Commands here:
        // e.g. AddSequential(new Command1());
        //      AddSequential(new Command2());
        // these will run in order.

        // To run multiple commands at the same time,
        // use AddParallel()
        // e.g. AddParallel(new Command1());
        //      AddSequential(new Command2());
        // Command1 and Command2 will run in parallel.

        // A command group will require all of the subsystems that each member
        // would require.
        // e.g. if Command1 requires chassis, and Command2 requires arm,
        // a CommandGroup containing them would require both the chassis and the
        // arm.
	rotateFirst = new Rotate("NavFirstRotate");
	driveStraight = new DriveStraight("NavStraight");
	rotateSecond = new Rotate("NavSecondRotate");
	firstRotateAngle=0;
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
	rotateFirst->SetGoal(firstRotateAngle,threshold,cooldown);
	driveStraight->SetGoal(moveDist,.05,1.5);
	rotateSecond->SetGoal(finalRotateAngle,2,1, false);
	// From X and Y coordinates and final angle calculate params for each step
}
/*
 * @param cartX offset from North, in feet. Positive is to the right
 * @param cartY offset toward the North, in feet.
 * @finalRotation the new North relative to initial North.
 */
void NavigateTo::SetGoalCartesian(double cartX, double cartY, double finalRotation){
	// It's X over Y because the angle is from the North
	firstRotateAngle = 360*atan2(cartX, cartY)/(2*3.1415926536);	
	moveDist = sqrt(cartX*cartX + cartY*cartY);
	SetGoalPolar(firstRotateAngle, moveDist, finalRotation);
}
/*
 * @rotate rotation angle
 * @distance distance in FEET
 */
void NavigateTo::SetGoalPolar(double rotate, double distance, double finalRotation){
	firstRotateAngle = rotate;
	finalRotateAngle = finalRotation - firstRotateAngle;
	moveDist = Chassis::feetToEncoderUnits(distance);
}

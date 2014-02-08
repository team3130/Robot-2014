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
	rotateFirst = new Rotate();
	driveStraight = new DriveStraight();
	rotateSecond = new Rotate();
	firstRotateAngle=0;
	AddSequential(rotateFirst);
	//AddSequential(driveStraight);
	//AddSequential(rotateSecond);
}

NavigateTo::~NavigateTo() {
	delete rotateFirst;
	delete driveStraight;
	delete rotateSecond;
}

void NavigateTo::Initialize()
{
	rotateFirst->SetGoal(firstRotateAngle,2,1);
	// From X and Y coordinates and final angle calculate params for each step
}
void NavigateTo::SetGoalCartesian(double cartX, double cartY, double finalRotation){
	firstRotateAngle = 360*atan2(cartX, cartY)/(2*3.1415926536);	
	finalRotateAngle = finalRotation;
	moveDist = sqrt(cartX*cartX + cartY*cartY);
	SetGoalPolar(firstRotateAngle, moveDist, finalRotateAngle);
}
void NavigateTo::SetGoalPolar(double rotate, double distance, double finalRotation){
	firstRotateAngle = rotate;
	finalRotateAngle = finalRotation;
	moveDist = distance;
}

#include "NavigateTo.h"

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
	AddSequential(rotateFirst);
	AddSequential(driveStraight);
	AddSequential(rotateSecond);
}

NavigateTo::~NavigateTo() {
	delete rotateFirst;
	delete driveStraight;
	delete rotateSecond;
}

void Initialize()
{
	// From X and Y coordinates and final angle calculate params for each step
}

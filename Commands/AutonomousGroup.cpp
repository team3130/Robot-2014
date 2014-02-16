#include "AutonomousGroup.h"

AutonomousGroup::AutonomousGroup() {
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
	
	// allocate and store pointers to commands
	idle = new IdleIntake();
	driveStraight1 = new DriveStraightGyro("Initial Drive");
	waitForHot = new WaitForHot();
	shoot = new ShootCatapult();
	driveStraight2 = new DriveStraightGyro("Auto Straight");
	
	// idle
	AddSequential(idle);
	
	// drive forward to best shooting position (controlled via dashboard var) 
	AddSequential(driveStraight1);
	
	// wait until the goal is hot, could be now, might be @ seconds
	AddSequential(waitForHot);
	
	// shoot
	AddSequential(shoot);
	
	// drive forward to ensure we cross into the next zone
	AddSequential(driveStraight2);
}

AutonomousGroup::~AutonomousGroup(){
	if ( idle )
		delete idle;
	if ( driveStraight1 )
		delete driveStraight1;
	if ( waitForHot )
		delete waitForHot;
	if ( shoot )
		delete shoot;
	if ( driveStraight2 )
		delete driveStraight2;
}

void AutonomousGroup::Initialize(){
	
	double dDistanceToMove = CommandBase::preferences->GetDouble("AutonomousInitialMoveDistance",0.0);
	double dSpeed = CommandBase::preferences->GetDouble("AutonomousDriveSpeed",2.0);

	// calculate seconds of movement based on distance to move and speed
	double dSeconds = dDistanceToMove / dSpeed;

	// set pre-shot drive strait params
	driveStraight1->SetGoal( dSeconds, dSpeed );

	// if we didn't move far enough on the pre-shot move, move forward a few feet
	if ( dDistanceToMove < 4.0 ) {
		dSpeed = 2.0;
		dSeconds = 2.0;
	// else don't move (much)
	} else {
		dSpeed = 0.1;
		dSeconds = 0.1;
	}
	driveStraight2->SetGoal(dSeconds,dSpeed);
}

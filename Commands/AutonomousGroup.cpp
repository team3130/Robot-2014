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
	
	// store default autonomous values in the dashboard
	SmartDashboard::PutNumber("Autonomous Move To Shoot Distance",0.0);
	SmartDashboard::PutNumber("Autonomous Drive Speed",0.8);

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
	
	double dDistanceToMove = SmartDashboard::GetNumber("Autonomous Move To Shoot Distance");
	double dSpeed = SmartDashboard::GetNumber("Autonomous Drive Speed");
	
	double dSeconds = dDistanceToMove / dSpeed;
	
	//if robot has moved less than a certain distance, then it will move again to ensure that it's in the zone
	driveStraight1->SetGoal(dSeconds,dSpeed);
	if(dDistanceToMove < 3){
		dSpeed = 0.1;
		dSeconds = 0.1;
	}
	driveStraight2->SetGoal(dSeconds,dSpeed);
}

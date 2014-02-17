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

	// LED relay
	// TODO pLEDRelay = new DigitalOutput(5);
	
	// allocate and store pointers to commands
	idle = new IdleIntake();
	driveStraight1 = new DriveStraight("Initial Drive");
	waitForHot = new WaitForHot("Wait for Hot Goal");
	shoot = new ShootCatapult("Auto Shoot");
	//when true, winch is pulled back.
	driveStraight2 = new DriveStraight("Auto Straight");
	
	// idle
	AddSequential(idle);
	
	// drive forward to best shooting position (controlled via dashboard var) 
	//AddSequential(driveStraight1);
	
	// wait until the goal is hot, could be now, might be @ seconds
	//AddSequential(waitForHot);
	
	// shoot
	AddSequential(shoot);
	SmartDashboard::PutData("auto command", this);
	
	// drive forward to ensure we cross into the next zone
	//AddSequential(driveStraight2);
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
	// if ( pLEDRelay ) todo
		// delete pLEDRelay; todo
}

void AutonomousGroup::Initialize(){
	
	// turn on the led
	// if ( pLEDRelay ) todo
		// pLEDRelay->Set(1); todo

	driveStraight1->SetGoal(
			Robot::preferences->GetDouble("AutonomousInitialMoveDistance",0.0),
			Robot::preferences->GetDouble("AutonomousInitialMoveTolerance",0.5)
		);
	driveStraight2->SetGoal(
			Robot::preferences->GetDouble("AutonomousFinalMoveDistance",4.0),
			Robot::preferences->GetDouble("AutonomousFinalMoveTolerence",0.5)
		);
}

// Called once after isFinished returns true
void AutonomousGroup::End() {
	// turn off the led
	// if ( pLEDRelay ) todo
		// pLEDRelay->Set(0); todo
}

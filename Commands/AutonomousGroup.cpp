#include "AutonomousGroup.h"
#include "WindCatapult.h"

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

	SmartDashboard::PutNumber("Autonomous - Init Move Dist", 0);
	SmartDashboard::PutNumber("Autonomous - Init Move Tol", 0.5);

	SmartDashboard::PutNumber("Autonomous - Final Move Dist", 1);
	SmartDashboard::PutNumber("Autonomous - Final Move Tol", 0.5);

	// allocate and store pointers to commands
	idle = new IdleIntake();
	waitForHot1 = new WaitForHot("Check for Hot Goal");
	driveStraight1 = new DriveStraightGyro("Initial Drive");
	waitForHot2 = new WaitForHot("Wait for Hot Goal");
	shoot = new ShootCatapult("Auto Shoot");
	WindCatapult* wind = new WindCatapult("Wind Back Catapult");
	//when true, winch is pulled back.
	driveStraight2 = new DriveStraightGyro("Auto Straight");
	
	// idle
	AddParallel(wind);
	AddSequential(idle);
	
	// check for hot, store result as waitforhot static
	AddSequential(waitForHot1);

	// drive forward to best shooting position (controlled via dashboard var) 
	AddSequential(driveStraight1);
	
	// check stored is-hot value, return immediatly if hot, otherwise wait five seconds
	AddSequential(waitForHot2);
	
	// shoot
	AddSequential(shoot);
	
	// drive forward to ensure we cross into the next zone
	AddSequential(driveStraight2);
}

AutonomousGroup::~AutonomousGroup(){
	if ( idle )
		delete idle;
	if ( waitForHot1 )
		delete waitForHot1;
	if ( driveStraight1 )
		delete driveStraight1;
	if ( waitForHot2 )
		delete waitForHot2;
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
	WaitForHot::sm_bIsHot = false;
	WaitForHot::sm_bInitialCheck = true;
	
	// driveStraight1->SetGoal(0,0.0);
	driveStraight1->SetGoal(
			SmartDashboard::GetNumber("Autonomous - Init Move Dist"),
			SmartDashboard::GetNumber("Autonomous - Init Move Tol")
		);
	/*driveStraight1->SetGoal(
			Robot::preferences->GetDouble("AutonomousInitialMoveDistance",0.0),
			Robot::preferences->GetDouble("AutonomousInitialMoveTolerance",0.5)
		);*/
	// driveStraight2->SetGoal(2,0.5);
	driveStraight2->SetGoal(
			SmartDashboard::GetNumber("Autonomous - Final Move Dist"),
			SmartDashboard::GetNumber("Autonomous - Final Move Tol")
		);
	/*driveStraight2->SetGoal(
			Robot::preferences->GetDouble("AutonomousFinalMoveDistance",4.0),
			Robot::preferences->GetDouble("AutonomousFinalMoveTolerence",0.5)
		);*/
}

// Called once after isFinished returns true
void AutonomousGroup::End() {
	// turn off the led
	// if ( pLEDRelay ) todo
		// pLEDRelay->Set(0); todo
}

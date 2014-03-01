#include "AutonomousGroup.h"
#include "WindCatapult.h"

AutonomousGroup::AutonomousGroup() {
	SmartDashboard::PutNumber("Autonomous - Init Move Dist", 0);
	SmartDashboard::PutNumber("Autonomous - Init Move Tol", 0.5);

	SmartDashboard::PutNumber("Autonomous - Final Move Dist", 1);
	SmartDashboard::PutNumber("Autonomous - Final Move Tol", 0.5);

	// allocate and store pointers to commands
	loader = new WindCatapult("Auto: Load Catapult");
	waitForHot = new WaitForHot("Check for Hot Goal");
	driveStraight1 = new DriveStraight("Auto: get to fire line ");
	shoot = new ShootCatapult("Auto: Shoot");
	driveStraight2 = new DriveStraight("Auto: clear the zone");

	// Do the whole reload procedure mainly to fill up the accumulator
	AddParallel(loader);
	// check for hot, store result as waitforhot static
	AddParallel(waitForHot);

	AddSequential(driveStraight1);
	AddSequential(shoot);
	AddSequential(driveStraight2);
	AddSequential(new WindCatapult("Auto: Reload Catapult"));
}

AutonomousGroup::~AutonomousGroup(){
		delete waitForHot;
		delete driveStraight1;
		delete shoot;
		delete driveStraight2;
}

void AutonomousGroup::Initialize(){
	WaitForHot::sm_bIsHot = false;
	WaitForHot::sm_bInitialCheck = true;
	CommandBase::stopper->Calibrate(0);
	CommandBase::intake->SetIdle(true);
	driveStraight1->SetGoal(
			SmartDashboard::GetNumber("Autonomous - Init Move Dist"),
			SmartDashboard::GetNumber("Autonomous - Init Move Tol")
		);
	driveStraight2->SetGoal(
			SmartDashboard::GetNumber("Autonomous - Final Move Dist"),
			SmartDashboard::GetNumber("Autonomous - Final Move Tol")
		);
	hotGoalTimer.Reset();
	hotGoalTimer.Start();
}

void AutonomousGroup::Execute(){
	if(loader->IsFinished()){
		if(waitForHot->sm_bIsHot || hotGoalTimer.Get()>=5.0){
			shoot->GrantPermission(true);
		}
	}
}

// Called once after isFinished returns true
void AutonomousGroup::End() {
}

#include "AutonomousGroup.h"
#include "WindCatapult.h"

AutonomousGroup::AutonomousGroup() {
	SmartDashboard::PutNumber("Auton - Init Move Dist", -140);
	SmartDashboard::PutNumber("Auton - Init Move Tol", 0.5);
	SmartDashboard::PutNumber("Auton - Init Move Speed", 0.5);

	SmartDashboard::PutNumber("Auton - Final Move Dist", -0);
	SmartDashboard::PutNumber("Auton - Final Move Tol", 0.5);
	SmartDashboard::PutNumber("Auton - Final Move Speed", 0.5);

	SmartDashboard::PutNumber("Auton - Initial Shoot Time", 3.0);
	// allocate and store pointers to commands
	loader = new WindCatapult("Auto: Load Catapult");
	waitForHot = new WaitForHot("Check for Hot Goal");
	driveStraight1 = new DriveStraight("Auto: get to fire line ");
	shoot = new ShootCatapult("Auto: Shoot");
	driveStraight2 = new DriveStraight("Auto: clear the zone");
	accum = new AccumulateCatapult("Auto: Accum");
	// Do the whole reload procedure mainly to fill up the accumulator
	// check for hot, store result as waitforhot static
	AddParallel(accum);
	AddSequential(waitForHot);
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
	CommandBase::intake->ResetIdleTimer();
	WaitForHot::sm_bIsHot = false;
	CommandBase::stopper->Calibrate(SmartDashboard::GetNumber("Stopper High Angle"));
	CommandBase::intake->SetIdle(true);
	shoot->GrantPermission(false);
	driveStraight1->SetGoal(
			SmartDashboard::GetNumber("Auton - Init Move Dist"),
			SmartDashboard::GetNumber("Auton - Init Move Tol"),
			SmartDashboard::GetNumber("Auton - Init Move Speed")
		);
	driveStraight2->SetGoal(
			SmartDashboard::GetNumber("Auton - Final Move Dist"),
			SmartDashboard::GetNumber("Auton - Final Move Tol"),
			SmartDashboard::GetNumber("Auton - Final Move Speed")
		);
	hotGoalTimer.Reset();
	hotGoalTimer.Start();
}

void AutonomousGroup::Execute(){
	double waitTime = SmartDashboard::GetNumber("Auton - Initial Shoot Time");
	if(accum->IsFinished()){
		if((waitForHot->sm_bIsHot && (hotGoalTimer.Get() >= waitTime))|| hotGoalTimer.Get() >= 5.5){
			shoot->GrantPermission(true);
		}
	}
}

// Called once after isFinished returns true
void AutonomousGroup::End() {
}

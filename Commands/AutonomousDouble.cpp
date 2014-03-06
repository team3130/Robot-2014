#include "AutonomousDouble.h"
#include "WindCatapult.h"

AutonomousDouble::AutonomousDouble() {
	SmartDashboard::PutNumber("Autonomous - Get Ball Dist", 8);
	SmartDashboard::PutNumber("Autonomous - Get Ball Tol", 0.5);

	SmartDashboard::PutNumber("Autonomous - Clear Zone Dist", -50);
	SmartDashboard::PutNumber("Autonomous - Clear Zone Tol", 0.5);

	driveToBall = new DriveStraight("Auto: get second ball");
	shoot1 = new ShootCatapult("Auto: Shoot1");
	shoot2 = new ShootCatapult("Auto: Shoot2");
	driveZone = new DriveStraight("Auto: clear the zone");
	accum = new AccumulateCatapult("Auto: Accum");
	AddSequential(accum);
	AddSequential(shoot1);
	AddParallel(new WindCatapult("Auto: Reload Catapult1"));
	AddParallel(driveToBall);
	AddSequential(getBall);
	AddSequential(shoot2);
	AddParallel(new WindCatapult("Auto: Reload Catapult2"));
	AddSequential(driveZone);
}

AutonomousDouble::~AutonomousDouble(){
	delete driveToBall;
	delete shoot1;
	delete shoot2;
	delete driveZone;
}

void AutonomousDouble::Initialize(){
	CommandBase::intake->ResetIdleTimer();
	CommandBase::stopper->Calibrate(SmartDashboard::GetNumber("Stopper High Angle"));
	CommandBase::intake->ExtendArms(true);
	shoot1->GrantPermission(false);
	shoot2->GrantPermission(false);

	driveToBall->SetGoal(
			SmartDashboard::GetNumber("Autonomous - Get Ball Dist"),
			SmartDashboard::GetNumber("Autonomous - Get Ball Tol")
		);
	driveZone->SetGoal(
			SmartDashboard::GetNumber("Autonomous - Clear Zone Dist"),
			SmartDashboard::GetNumber("Autonomous - Clear Zone Tol")
		);
}

void AutonomousDouble::Execute(){
	if(accum->IsFinished()){
		shoot1->GrantPermission(true);
	}
}

// Called once after isFinished returns true
void AutonomousDouble::End() {
}

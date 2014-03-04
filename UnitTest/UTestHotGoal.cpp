#include "UTestHotGoal.h"

UTestHotGoal::UTestHotGoal() : CommandGroup("UTest Hot Goal") {
	waitForHot = new WaitForHot("Check for Hot Goal");
	AddParallel(waitForHot);
}

UTestHotGoal::~UTestHotGoal(){
	delete waitForHot;
}

void UTestHotGoal::Initialize(){
	WaitForHot::sm_bIsHot = false;
	WaitForHot::sm_bInitialCheck = true;
	hotGoalTimer.Reset();
	hotGoalTimer.Start();
}

void UTestHotGoal::Execute(){
	SmartDashboard::PutBoolean("UTest Goal is HOT",waitForHot->sm_bIsHot);
	SmartDashboard::PutNumber( "UTest Goal hot timer",hotGoalTimer.Get());
}

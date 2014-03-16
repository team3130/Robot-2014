#include "UTestHotGoal.h"

UTestHotGoal::UTestHotGoal() : CommandGroup("UTest Hot Goal") {
	waitForHot = new WaitForHot("Unit Test for Hot Goal");
	AddParallel(waitForHot);
	SmartDashboard::PutData(this);
}

UTestHotGoal::~UTestHotGoal(){
	delete waitForHot;
}

void UTestHotGoal::Initialize(){
	WaitForHot::sm_bIsHot = false;
	hotGoalTimer.Reset();
	hotGoalTimer.Start();
}

void UTestHotGoal::Execute(){
	SmartDashboard::PutBoolean("UTest Goal is HOT",waitForHot->sm_bIsHot);
	SmartDashboard::PutNumber( "UTest Goal hot timer",hotGoalTimer.Get());
}

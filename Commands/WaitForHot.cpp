#include "WaitForHot.h"

bool WaitForHot::sm_bIsHot = false;
bool WaitForHot::sm_bInitialCheck = false;

WaitForHot::WaitForHot(const char* name) : CommandBase(name) {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	SmartDashboard::PutNumber("Autonomous - Hot Method", 0.0);
	
    distanceTracking = new DistanceTracking();
}

WaitForHot::~WaitForHot() {
	if ( distanceTracking )
		delete distanceTracking;
}

// Called just before this Command runs the first time
void WaitForHot::Initialize() {
	
	// hotMethod = (int) Robot::preferences->GetDouble("AutonomousDetectHotMethod",0.0);
	hotMethod = (int) SmartDashboard::GetNumber("Autonomous - Hot Method");
		
	hotCount = 0;
	hotIterate = 0;
	
	// reset the timer, then start again
	timer.Reset();
	timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void WaitForHot::Execute() {
	
	if ( !sm_bInitialCheck ) {
		return;
	}
	
	// wait until half a second has passed before checking for hot or not
	/*
	if ( !timer.HasPeriodPassed(0.5))
		return;
	*/
	
	//Check if half a second had passed
	if (timer.Get() >= .5){
		// we'll check for hot the first 10 times called (0-9)
		if ( hotIterate < 10 ) {
		
			// if using aimed method to test for hot
			if ( hotMethod == 0 ) {
				// if the aimed target is hot, increment hot count
				if ( distanceTracking->IsAimedTargetHot() ) {				
				hotCount ++;
				}
			
		// else use closest method for hot test
			} else {
				// if the closer target is hot, increment hot count
				if ( distanceTracking->IsClosestTargetHot() ) {
				hotCount ++;
				}
			}
			// increment hot iteration counter
			hotIterate++;
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool WaitForHot::IsFinished() {

	// if this is the first run of this command, just checking for hot
	// and setting a 
	if ( sm_bInitialCheck ) {
		// after the 10th hot check, check if we're hot  
		if ( hotIterate >= 10 ) {
			// if greater than five hots, assume hot, return true
			if ( hotCount > 5 ) {
				WaitForHot::sm_bIsHot = true;
			} else {
				WaitForHot::sm_bIsHot = false;
			}
			SmartDashboard::PutBoolean("IsHot", WaitForHot::sm_bIsHot);	
			SmartDashboard::PutNumber("Hot Count", hotCount);	
			WaitForHot::sm_bInitialCheck = false;
			return true;
		}
	}
	else {
		// if initial check indicated hot, return now
		if ( sm_bIsHot )
			return true;
		
		// else if it's been five seconds, return now
		if ( timer.HasPeriodPassed(5.0)) {
			return true;
		}
	}
	return false;
}

// Called once after isFinished returns true
void WaitForHot::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void WaitForHot::Interrupted() {
}

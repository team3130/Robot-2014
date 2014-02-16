#include "WaitForHot.h"

WaitForHot::WaitForHot() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
    distanceTracking = new DistanceTracking();
	SmartDashboard::PutData(this);
}

// Called just before this Command runs the first time
void WaitForHot::Initialize() {
	hotCount = 0;
	hotIterate = 0;
	//timer.Reset();
	timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void WaitForHot::Execute() {
	
	// we'll check for hot the first 10 times called (0-9)
	if ( hotIterate < 10 ) {
		// if the closer target is hot, increment hot count
		if ( distanceTracking->IsClosestTargetHot() ) {
			hotCount ++;
		}
		// increment hot iteration counter
		hotIterate++;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool WaitForHot::IsFinished() {
	if ( timer.HasPeriodPassed(5.0)) 
		return true;
	
	// after the 10th hot check, check if we're hot  
	if ( hotIterate == 10 ) {
		// if greater than five hots, assume hot, return true
		if ( hotCount > 5 ) {
			return true;
		}
		// increment hotIterate so that we don't bother checking again
		hotIterate++;
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

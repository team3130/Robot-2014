#include "WaitForHot.h"

WaitForHot::WaitForHot(const char* name) : CommandBase(name) {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
    distanceTracking = new DistanceTracking();
}

WaitForHot::~WaitForHot() {
	if ( distanceTracking )
		delete distanceTracking;
}

// Called just before this Command runs the first time
void WaitForHot::Initialize() {
	
	hotMethod = (int) Robot::preferences->GetDouble("AutonomousDetectHotMethod",0.0);
		
	hotCount = 0;
	hotIterate = 0;
	
	// reset the timer, then start again
	timer.Reset();
	timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void WaitForHot::Execute() {
	
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

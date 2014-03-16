#include "WaitForHot.h"

bool WaitForHot::sm_bIsHot = false;

WaitForHot::WaitForHot(const char* name) : CommandBase(name) {

	SmartDashboard::PutNumber("Auton - Hot Method", 2.0);
	SmartDashboard::PutNumber("Auton - Hot Scans", 15);
	SmartDashboard::PutNumber("Auton - Hot Confirms", 5);
	SmartDashboard::PutNumber("Auton - Init Wait", 0.7);
		
    distanceTracking = new DistanceTracking();
}

WaitForHot::~WaitForHot() {
	if ( distanceTracking )
		delete distanceTracking;
}

// Called just before this Command runs the first time
void WaitForHot::Initialize() {
	
	hotMethod = (int) SmartDashboard::GetNumber("Auton - Hot Method");
		
	hotCount = 0;
	hotIterate = 0;
	
	distanceTracking->countNoTable = 0;
	distanceTracking->countTooMany = 0;
	distanceTracking->countZeroRectangles = 0;
	
	hotScans = (int) SmartDashboard::GetNumber("Auton - Hot Scans");
	hotConfirms = (int) SmartDashboard::GetNumber("Auton - Hot Confirms");
	initWait = SmartDashboard::GetNumber("Auton - Init Wait");
	
	// reset the timer, then start again
	timer.Reset();
	timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void WaitForHot::Execute() {
		
	// wait a bit for checking for hot goal
	if ( timer.Get() >= initWait ) {

		// if using aimed method to test for hot
		if ( hotMethod == 0 ) {
			// if the aimed target is hot, increment hot count
			if ( distanceTracking->IsAimedTargetHot() ) {				
				hotCount ++;
			}
		}

		// else use closest method for hot test
		else if ( hotMethod == 1 ) {
			// if the closer target is hot, increment hot count
			if ( distanceTracking->IsClosestTargetHot() ) {
				hotCount ++;
			}
		}

		// else using roborealm shape matching, just check the value from the
		// network table
		else if ( hotMethod == 2 ) {
			NetworkTable * pNetworkTable = NetworkTable::GetTable("SmartDashboard");
			if ( pNetworkTable ) {
				if ( pNetworkTable->GetNumber("SHAPE_MATCH_HIT", 0.0) > 0.0 ) {
					hotCount++;
				}
			}
		}

		// increment hot iteration counter
		hotIterate++;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool WaitForHot::IsFinished() {

	// if we've iterated as many times as we were told to
	if ( hotIterate >= hotScans ) {
		
		// if our hot count exceeds or hits the hot confirm count, return true
		if ( hotCount >= hotConfirms ) {
			WaitForHot::sm_bIsHot = true;
		} else {
			WaitForHot::sm_bIsHot = false;
		}
		
		SmartDashboard::PutBoolean("Auton - IsHot", WaitForHot::sm_bIsHot);	
		SmartDashboard::PutNumber("Auton - Hot Count", hotCount);
		SmartDashboard::PutNumber("Auton - No Table count",distanceTracking->countNoTable);
		SmartDashboard::PutNumber("Auton - Zero Rects count",distanceTracking->countZeroRectangles);
		SmartDashboard::PutNumber("Auton - Too Many Rects count",distanceTracking->countTooMany);

		return true;
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

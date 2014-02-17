/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty                                                  */
/*-------------------------------------------------------------------------*/
#include "Robot.h"
#include "Commands/AutonomousGroup.h"

Preferences* Robot::preferences = NULL;
UnitTest* Robot::unitTest = NULL;

void Robot::RobotInit() {
	CommandBase::init();
	autonomousCommand = new AutonomousGroup();
	lw = LiveWindow::GetInstance();
	preferences = Preferences::GetInstance();
	unitTest = new UnitTest();
}

void Robot::AutonomousInit() {
	autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to 
	// continue until interrupted by another command, remove
	// this line or comment it out.
	autonomousCommand->Cancel();
	//SmartDashboard::PutData("Move Straight", new JoystickStraight(600,600));
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {
	lw->Run();
}

START_ROBOT_CLASS(Robot);


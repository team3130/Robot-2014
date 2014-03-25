/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty                                                  */
/*-------------------------------------------------------------------------*/
#include "Robot.h"
#include "Commands/AutonomousGroup.h"

UnitTest*    Robot::unitTest = NULL;

class CommandBasedRobot : public IterativeRobot {
private:
	Command *autonomousCommand;
	LiveWindow *lw;

	virtual void RobotInit() {
		CommandBase::init();
		Robot::unitTest = new UnitTest();
		autonomousCommand = new AutonomousGroup();
		lw = LiveWindow::GetInstance();
	}

	virtual void AutonomousInit() {
		autonomousCommand->Start();
	}
	
	virtual void AutonomousPeriodic() {
		Scheduler::GetInstance()->Run();
	}
	
	virtual void TeleopInit() {
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to 
		// continue until interrupted by another command, remove
		// this line or comment it out.
		// autonomousCommand->Cancel();
		//SmartDashboard::PutData("Move Straight", new JoystickStraight(600,600));
	}
	
	virtual void TeleopPeriodic() {
		Scheduler::GetInstance()->Run();
	}
	
	virtual void TestPeriodic() {
		lw->Run();
	}
};


START_ROBOT_CLASS(CommandBasedRobot);

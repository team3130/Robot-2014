/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty                                                  */
/*-------------------------------------------------------------------------*/
#include "Robot.h"
#include "Commands/AutonomousGroup.h"
#include "Subsystems/Logger.h"

Preferences* Robot::preferences = NULL;
UnitTest*    Robot::unitTest = NULL;
Logger* Robot::logger = NULL;

class CommandBasedRobot : public IterativeRobot {
private:
	Command *autonomousCommand;
	LiveWindow *lw;

	virtual void RobotInit() {
		Robot::logger = new Logger();
		CommandBase::init();
		autonomousCommand = new AutonomousGroup();
		lw = LiveWindow::GetInstance();
		Robot::preferences = Preferences::GetInstance();
		Robot::logger->update_number("TESTY", 3.14);
	}
	void getPreferencesData(){
		Robot::unitTest = new UnitTest();
		if(!Robot::preferences->ContainsKey("Arm Encoder Functional")){
			Robot::preferences->PutBoolean("Arm Encoder Functional", false);
		}
		if(!Robot::preferences->ContainsKey("StopperEncoderPPI")){
			Robot::preferences->PutDouble("StopperEncoderPPI", 114.53);
		}
		if(!Robot::preferences->ContainsKey("Stopper Winch Encoder Functional")){
			Robot::preferences->PutBoolean("Stopper Winch Encoder Functional", true);
		}
		Robot::preferences->GetBoolean("Arm Encoder Functional", false);
		Robot::preferences->GetBoolean("Stopper Winch Encoder Functional", true);
	}
	virtual void AutonomousInit() {
		getPreferencesData();
		autonomousCommand->Start();
	}
	
	virtual void AutonomousPeriodic() {
		Scheduler::GetInstance()->Run();
	}
	
	virtual void TeleopInit() {
		getPreferencesData();
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to 
		// continue until interrupted by another command, remove
		// this line or comment it out.
		autonomousCommand->Cancel();
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

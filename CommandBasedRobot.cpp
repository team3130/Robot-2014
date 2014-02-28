/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty                                                  */
/*-------------------------------------------------------------------------*/
#include "Robot.h"
#include "Commands/AutonomousGroup.h"

Preferences* Robot::preferences = NULL;
UnitTest*    Robot::unitTest = NULL;

void Robot::init(){
	Robot::preferences = Preferences::GetInstance();
	Robot::unitTest = new UnitTest();
	if(!Robot::preferences->ContainsKey("Left Encoder PPR")){
		Robot::preferences->PutInt("Left Encoder PPR", 256);
	}
	if(!Robot::preferences->ContainsKey("Right Encoder PPR")){
		Robot::preferences->PutInt("Right Encoder PPR", 256);
	}
	if(!Robot::preferences->ContainsKey("Low Gear Top Speed")){
		// Theoretical max speed of the bot on low gear in inches per second
		// Has to be unreachable closest amount.
		Robot::preferences->PutDouble("Low Gear Top Speed",150);
	}
	if(!Robot::preferences->ContainsKey("Arm Encoder Functional")){
		Robot::preferences->PutBoolean("Arm Encoder Functional", false);
	}
	if(!Robot::preferences->ContainsKey("StopperEncoderPPI")){
		Robot::preferences->PutDouble("StopperEncoderPPI", 114.53);
	}
	if(!Robot::preferences->ContainsKey("Stopper Winch Encoder Functional")){
		Robot::preferences->PutBoolean("Stopper Winch Encoder Functional", true);
	}
}

class CommandBasedRobot : public IterativeRobot {
private:
	Command *autonomousCommand;
	LiveWindow *lw;

	virtual void RobotInit() {
		Robot::init();
		CommandBase::init();
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

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

void Robot::init(){
	Robot::preferences = Preferences::GetInstance();
	if(!Robot::preferences->ContainsKey("LeftEncoderPPR")){
		Robot::preferences->PutInt("LeftEncoderPPR", 256);
	}
	if(!Robot::preferences->ContainsKey("RightEncoderPPR")){
		Robot::preferences->PutInt("RightEncoderPPR", 256);
	}
	if(!Robot::preferences->ContainsKey("LowGearTopSpeed")){
		// Theoretical max speed of the bot on low gear in inches per second
		// Has to be unreachable closest amount.
		Robot::preferences->PutDouble("LowGearTopSpeed",150);
	}
	if(!Robot::preferences->ContainsKey("ArmEncoderFunctional")){
		Robot::preferences->PutBoolean("ArmEncoderFunctional", false);
	}
	if(!Robot::preferences->ContainsKey("StopperEncoderPPI")){
		Robot::preferences->PutDouble("StopperEncoderPPI", 114.53);
	}
	if(!Robot::preferences->ContainsKey("StopperWinchEncoderFunctional")){
		Robot::preferences->PutBoolean("StopperWinchEncoderFunctional", true);
	}
	CommandBase::init();
	Robot::unitTest = new UnitTest();
}

class CommandBasedRobot : public IterativeRobot {
private:
	Command *autonomousCommand;
	LiveWindow *lw;

	virtual void RobotInit() {
		Robot::logger = new Logger();
		CommandBase::init();
		autonomousCommand = new AutonomousGroup();
		lw = LiveWindow::GetInstance();
		Robot::logger->update_number("TESTY", 3.14);
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

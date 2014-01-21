#include "WPILib.h"
#include "Commands/Command.h"
#include "Commands/ExampleCommand.h"
#include "CommandBase.h"
#include "string.h"
#include "Commands/MoveStraight.h"

class CommandBasedRobot : public IterativeRobot {
private:
	Command *autonomousCommand;
	LiveWindow *lw;
	
	virtual void RobotInit() {
		CommandBase::init();
		autonomousCommand = new ExampleCommand();
		lw = LiveWindow::GetInstance();
	}
	
	virtual void AutonomousInit() {
		using namespace std;
		string s1="hello";
		string s2("there");
		string s3=s1+s2;
		string s4=s1.append(s2.begin(),s2.end());
		string s5="chicken ";
		s5+="nuggets";
		string s6="french ";
		string s7="fries";
		s6+=s7;
		SmartDashboard::PutString("s1",s1);
		SmartDashboard::PutString("s2",s2);
		SmartDashboard::PutString("s3",s3);
		SmartDashboard::PutString("s4",s4);
		SmartDashboard::PutString("s5",s5);
		SmartDashboard::PutString("s6",s6);
		SmartDashboard::PutString("s7",s7);
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
		SmartDashboard::PutData("Move Straight", new MoveStraight(600,600));
	}
	
	virtual void TeleopPeriodic() {
		Scheduler::GetInstance()->Run();
	}
	
	virtual void TestPeriodic() {
		lw->Run();
	}
};

START_ROBOT_CLASS(CommandBasedRobot);


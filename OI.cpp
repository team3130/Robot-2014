#include "OI.h"
#include "Commands/JoystickStraight.h"
#include "Commands/JoystickTank.h"
#include "Commands/Rotate.h"
#include "Commands/DriveStraight.h"
#include "Commands/Rotate.h"

OI::OI() {
	leftJoystick = new Joystick(1);
	rightJoystick = new Joystick(2);
	gamepad= new Joystick(3);
	leftPrecision = new JoystickButton(leftJoystick, 1);
	rightPrecision = new JoystickButton(rightJoystick, 1);
	straightMode = new JoystickButton(rightJoystick, 2);
	straightMode->WhenPressed(new JoystickStraight());
	SmartDashboard::PutNumber("Drive Straight",720);
	SmartDashboard::PutNumber("Drive Straight P",0.001);
	SmartDashboard::PutNumber("Drive Straight I",0);
	SmartDashboard::PutNumber("Drive Straight D",0);
	driveTest = new JoystickButton(leftJoystick, 3);
	rotateTest = new JoystickButton(leftJoystick, 5);
	//DriveStraight* t = new DriveStraight(0,0,0,0,0,0);
	//driveTest->WhenPressed((Command*)t);
	driveTest->WhenPressed(new DriveStraight(SmartDashboard::GetNumber("Drive Straight"),0.05,1, SmartDashboard::GetNumber("Drive Straight P"), SmartDashboard::GetNumber("Drive Straight I"), SmartDashboard::GetNumber("Drive Straight D")));
	rotateTest->WhenPressed(new Rotate(180,1,1,-1,0,0));
		
	//straightMode->WhenReleased(new JoystickTank());

	SmartDashboard::PutNumber("Rotate",90.0);	// degrees
	SmartDashboard::PutNumber("Rotate PID P",1.0);
	SmartDashboard::PutNumber("Rotate PID I",0);
	SmartDashboard::PutNumber("Rotate PID D",0);
	SmartDashboard::PutNumber("Rotate Tolerance",5.0); // degrees
	SmartDashboard::PutNumber("Rotate Slowdown",30.0); // if above then full speed
	btnTest2 = new JoystickButton(leftJoystick, 4);
	btnTest2->WhenPressed(new Rotate(
			SmartDashboard::GetNumber("Rotate"),
			SmartDashboard::GetNumber("Rotate PID P"),
			SmartDashboard::GetNumber("Rotate PID I"),
			SmartDashboard::GetNumber("Rotate PID D")
			));
}

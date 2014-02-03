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
//	SmartDashboard::PutNumber("Drive Straight",720);
//	SmartDashboard::PutNumber("Drive Straight P",0.001);
//	SmartDashboard::PutNumber("Drive Straight I",0);
//	SmartDashboard::PutNumber("Drive Straight D",0);
	driveTest = new JoystickButton(leftJoystick, 3);
	rotateTest = new JoystickButton(leftJoystick, 5);
	//DriveStraight* t = new DriveStraight(0,0,0,0,0,0);
	//driveTest->WhenPressed((Command*)t);
	driveTest->WhenPressed(new DriveStraight(300,0.05,1,0,0,0));
	rotateTest->WhenPressed(new Rotate(180,1,1,-1,0,0));
		
	//straightMode->WhenReleased(new JoystickTank());
}

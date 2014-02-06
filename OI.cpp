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
}

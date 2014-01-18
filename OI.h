#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:

public:
	OI();
	Joystick* leftJoystick;
	Joystick* rightJoystick;
	Joystick* gamepad;
	JoystickButton* leftPrecision;
	JoystickButton* rightPrecision;
};

#endif

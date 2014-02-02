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
	JoystickButton* straightMode;
	JoystickButton* driveTest;
<<<<<<< HEAD
	JoystickButton* rotateTest;
=======
	JoystickButton* btnTest2;
>>>>>>> 47bea4b9c9d7b12b7e1199060397fac8ff3aacdd
};

#endif

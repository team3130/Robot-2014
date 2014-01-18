#ifndef CHASSIS_H
#define CHASSIS_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Chassis: public Subsystem {
private:
	RobotDrive* drive;
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	float precisionMultiplier;	//how much precision each level gives us.
	int precisionLevel;			//level of precision we want. 0 is default
	int maxPrecisionLevel;		//maximum precision level.
	Chassis();
	Chassis(int leftMotorChannel, int rightMotorChannel);
	void InitDefaultCommand();
	void tankDrive(Joystick* left, Joystick* right, int precision);
//	void morePrecision();
//	void lessPrecision();
//	void resetPrecision();
};

#endif

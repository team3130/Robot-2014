#ifndef CHASSIS_H
#define CHASSIS_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../NaivePidController.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Chassis: public Subsystem{
private:
	RobotDrive* drive;
	Jaguar* left;
	Jaguar* right;
	Timer PIDTimer;
public:
	NaivePIDController leftpc;
	NaivePIDController rightpc;
	NaivePIDController leftvc;
	NaivePIDController rightvc;
	Encoder* leftEncoder;
	Encoder* rightEncoder;
	
	Chassis();
	Chassis(int leftMotorChannel, int rightMotorChannel);
	void InitDefaultCommand();
	void tankDrive(float leftSpeed, float rightSpeed);
	
//	void morePrecision();
//	void lessPrecision();
//	void resetPrecision();
};

#endif

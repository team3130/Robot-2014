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
	double bias;
	double rightInvert;
	double leftInvert;
public:
	Encoder* leftEncoder;
	Encoder* rightEncoder;
	
	Chassis();
	Chassis(int leftMotorChannel, int rightMotorChannel);
	void InitDefaultCommand();
	void tankDrive(float leftSpeed, float rightSpeed);
	void arcadeDrive(float move, float turn);
	void straightDrive(float speed);
	
//	void morePrecision();
//	void lessPrecision();
//	void resetPrecision();
};

#endif

#ifndef CHASSIS_H
#define CHASSIS_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../NaivePidController.h"
#include "../EncoderRobotDrive.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Chassis: public Subsystem{
private:
	EncoderRobotDrive* drive;
	Jaguar* left;
	Jaguar* right;
	Gyro* gyro;
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
	void resetBias();
	
//	void morePrecision();
//	void lessPrecision();
//	void resetPrecision();
};

#endif

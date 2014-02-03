#ifndef CHASSIS_H
#define CHASSIS_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../NaivePidController.h"
#include "../EncoderRobotDrive.h"
#include "string.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Chassis: public Subsystem{
private:
	Jaguar* leftController;
	Jaguar* rightController;
	double bias;
	double rightInvert;
	double leftInvert;
public:
	EncoderRobotDrive* drive;
	Encoder* leftEncoder;
	Encoder* rightEncoder;
	Gyro* gyro;
	Chassis();
	Chassis(int leftMotorChannel, int rightMotorChannel);
	virtual ~Chassis();
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

#ifndef CHASSIS_H
#define CHASSIS_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
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
	static const int ENCODER_TOP_SPEED=3000;
	static const double WHEEL_RADIUS_INCHES=2;
	EncoderRobotDrive* drive;
	Encoder* leftEncoder;
	Encoder* rightEncoder;
	Gyro* gyro;
<<<<<<< HEAD
	
=======

>>>>>>> 47bea4b9c9d7b12b7e1199060397fac8ff3aacdd
	Chassis();
	Chassis(int leftMotorChannel, int rightMotorChannel);
	virtual ~Chassis();
	void InitDefaultCommand();
	void tankDrive(float leftSpeed, float rightSpeed);
	void arcadeDrive(float move, float turn);
	void straightDrive(float speed);
	void resetBias();
	static double encoderUnitsToFeet(double in);
	static double feetToEncoderUnits(double in);
	
	
//	void morePrecision();
//	void lessPrecision();
//	void resetPrecision();
};

#endif

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
public:
	static const int ENCODER_TOP_SPEED=3000;
	static const double WHEEL_RADIUS_INCHES=2;
	EncoderRobotDrive* drive;
	Encoder* leftEncoder;
	Encoder* rightEncoder;
	Gyro* gyro;
	Chassis();
	virtual ~Chassis();
	void InitDefaultCommand();
	void tankDrive(float leftSpeed, float rightSpeed);
	void arcadeDrive(float move, float turn);
	static double encoderUnitsToFeet(double in);
	static double feetToEncoderUnits(double in);
};

#endif

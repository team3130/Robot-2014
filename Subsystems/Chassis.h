#ifndef CHASSIS_H
#define CHASSIS_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "VelocityController.h"
#include "string.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Chassis: public Subsystem{
private:
	VelocityController* leftController;
	VelocityController* rightController;
public:
	static const int ENCODER_TOP_SPEED=3000;
	static const double WHEEL_RADIUS_INCHES=2;
	RobotDrive* drive;
	Gyro* gyro;
	Chassis();
	virtual ~Chassis();
	void InitDefaultCommand();
	void InitEncoders();
	void tankDrive(float leftSpeed, float rightSpeed);
	void arcadeDrive(float move, float turn);
	void SmartRobot(bool smart=true);
	void DumbRobot() {SmartRobot(false);}
	void ProjectSensors();
	double GetDistance();
	static double encoderUnitsToFeet(double in);
	static double feetToEncoderUnits(double in);
};

#endif

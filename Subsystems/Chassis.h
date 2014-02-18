/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty, Mikhail Kyraha                                  */
/*-------------------------------------------------------------------------*/
#ifndef CHASSIS_H
#define CHASSIS_H
#include "../Robot.h"
#include "../Logger/LogSubsystem.h"
#include "VelocityController.h"
#include "string.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Chassis: public LogSubsystem {
public:
	VelocityController* leftController;
	VelocityController* rightController;
	Solenoid* shifter;
	static const int ENCODER_TOP_SPEED = 3000;
	static const double WHEEL_RADIUS_INCHES = 2;
	RobotDrive* drive;
	Gyro* gyro;
	Chassis();
	virtual ~Chassis();
	void InitDefaultCommand();
	void InitLogCommand();
	void InitEncoders();
	void tankDrive(float leftSpeed, float rightSpeed);
	void arcadeDrive(float move, float turn);
	void SmartRobot(bool smart = true);
	void DumbRobot() {
		SmartRobot(false);
	}
	void ProjectSensors();
	double GetDistance();
	static double encoderUnitsToFeet(double in);
	static double feetToEncoderUnits(double in);
	void ShiftGear(bool isHigh);
	bool GetShiftPos();
};

#endif

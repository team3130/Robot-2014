/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty, Mikhail Kyraha                                  */
/*-------------------------------------------------------------------------*/
#ifndef CHASSIS_H
#define CHASSIS_H
#include "../Robot.h"
#include "Commands/Subsystem.h"
#include "VelocityController.h"
#include "string.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Chassis: public Subsystem{
private:
	static const int ENCODER_TOP_SPEED = 7200;
	static bool isUsingEncoders;
	static bool isUsingGyro;
	VelocityController* leftController;
	VelocityController* rightController;
	Solenoid* shifter;
public:
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
	bool CanUseEncoders() {return isUsingEncoders;}
	bool CanUseGyro() {return isUsingGyro;}
	double LowGearTopSpeed() {return encoderUnitsToFeet(ENCODER_TOP_SPEED);}
	void ProjectSensors();
	double GetDistance();
	static double encoderUnitsToFeet(double in);
	static double feetToEncoderUnits(double in);
	void ShiftGear(bool isHigh);
};

#endif

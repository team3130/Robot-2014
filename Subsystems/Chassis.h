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
	bool isLeftEncoderOK;
	bool isRightEncoderOK;
	bool isUsingGyro;
	VelocityController* leftController;
	VelocityController* rightController;
	Solenoid* shifter;
public:
	RobotDrive* drive;
	Gyro* gyro;
	Chassis();
	void InitDefaultCommand();
	void InitEncoders();
	void tankDrive(float leftSpeed, float rightSpeed);
	void arcadeDrive(float move, float turn);
	void SmartRobot(bool smart=true);
	void DumbRobot() {SmartRobot(false);}
	bool CanUseEncoders() {return isLeftEncoderOK&&isRightEncoderOK;}
	bool CanUseGyro() {return isUsingGyro;}
	void ProjectSensors();
	double GetDistance();
	double GetRate();
	static double encoderUnitsToFeet(double in);
	static double feetToEncoderUnits(double in);
	void ShiftGear(bool isHigh);
};

#endif

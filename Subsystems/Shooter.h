/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Kevin Bi, James Li, Zhenghao Zhu                               */
/*-------------------------------------------------------------------------*/

#ifndef SHOOTER_H
#define SHOOTER_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

class Shooter: public Subsystem {
private:
	Solenoid* shoot;
	Jaguar* winch;
	Jaguar* stop;
	//current catapult position
	double catapultPosition;
	//current end position
	double endPosition;
	////Amount catapult should move when shooting *currently unused
	//double shootMovement;
	////Amount of time shooting movement should take (To adjust speed) *currently unused
	//double shootTime;
public:
	Encoder* winchEncoder;
	Encoder* stopEncoder;
	
	Shooter();
	Shooter(int winchMotorChannel, int stopMotorChannel, int shootChannel);
	~Shooter();
	void InitDefaultCommand();
	void adjustCatapult(double level, double time);
	void adjustEnd(double newEndPosition, double time);
	void setWinchSpeed(double speed);
	void setStopSpeed(double speed);
	void setShoot(bool toggle);
	double getCatapultPosition();
	double getEndPosition();
	bool getShootToggle();
};

#endif

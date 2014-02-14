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
	Solenoid* pinch;
	Jaguar* winch;
	Jaguar* stop;
	//current catapult position
	double winchPosition;
	//current end position
	double endPosition;
	////Amount catapult should move when shooting *currently unused
	//double shootMovement;
	////Amount of time shooting movement should take (To adjust speed) *currently unused
	//double shootTime;
	
	//Boolean for whether catapult is ready to fire
	bool Ready;
public:
	//Need to differentiate between Winch Encoder and Catapult Encoder
	
	Encoder* winchEncoder;
	Encoder* stopEncoder;
	
	Shooter();
	Shooter(int winchMotorChannel, int stopMotorChannel, int shootChannel);
	~Shooter();
	void InitDefaultCommand();
	void adjustCatapult(double level, double time);
	void adjustEnd(double newEndPosition, double time);
	//Get/set functions
	void setWinchSpeed(double speed);
	void setStopSpeed(double speed);
	void setShoot(bool toggle);
	double getWinchPosition();
	void setWinchPosition(double pos);
	double getCatapultPosition();
	double getEndPosition();
	bool getPinch();
	void setPinch(bool value);
	void setReady(bool value);
	bool getReady();
};

#endif

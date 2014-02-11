/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li, Zhenghao Zhu                                         */
/*-------------------------------------------------------------------------*/

#ifndef SHOOTER_H
#define SHOOTER_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

class Shooter: public Subsystem {
private:
	Solenoid* shoot;
	Jaguar* winch;
	double catapultPosition;
	bool toggle;
public:
	Encoder* winchEncoder;
	
	Shooter();
	Shooter(int winchMotorChannel, int shootChannel);
	~Shooter();
	void InitDefaultCommand();
	void adjustCatapult(double level, double time);
	void Shoot();
};

#endif

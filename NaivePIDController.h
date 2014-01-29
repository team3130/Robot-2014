/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty, Mikhail Kyraha                                  */
/*-------------------------------------------------------------------------*/

#ifndef NPID_CONTROLLER
#define NPID_CONTROLLER

#include "WPILib.h"
#include "string.h"

class NaivePIDController{
public:
	float currentError;
	float setPoint;
	float P, I, D;
	float accum;
	long lastSetTime;
	float lastError;
	std::string name;
	NaivePIDController(string name);
	float update(float value, long time);
	void resetTime();
	void reset();
	void setSetPoint(float in);
	void set(float P, float I, float D);
private:
	Timer timer;
	void projectPIDValues();
	void getPIDValues();
};
#endif

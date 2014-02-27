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
	Solenoid* pinch1;
	Solenoid* pinch2;
	Jaguar* winch;
	DigitalInput* limitSwitch;
	double catapultPosition;
	bool toggle;
	//Is the robot ready to shoot
	bool Ready;
	//The state of the Stop Motor (Lob or Shoot)
	int StopState; 
	Timer timer;
public:
	//Encoder* winchEncoder;
	//Encoder* armEncoder;
	Shooter();
	Shooter(int winchMotorChannel, int shootChannel1, int shootChannel2);
	~Shooter();
	void InitDefaultCommand();
	void adjustCatapult(double level, double time);
	void setWinchDirect(double speed);
	void SetShoot(bool in);
	void LockPincher(bool lock=true);
	void UnlockPincher() {LockPincher(false);}
	void ProjectSensors();
	
	//Get/set methods
	bool hasSlack();
	//double getWinchPosition();
	bool getPinch1();
	bool getPinch2();
	bool getReady();
	void setWinchSpeed(double speed);
	void setPinch(bool on);
	void setReady(bool value);
	void setStopState(int value);
};

#endif

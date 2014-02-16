/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li, Zhenghao Zhu                                         */
/*-------------------------------------------------------------------------*/

#ifndef STOPPERWINCH_H
#define STOPPERWINCH_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

class StopperWinch: public Subsystem {
private:
	Talon* stopper;
	DigitalInput* limitSwitch;
	double catapultPosition;
	double stopGoal;	//in inches.
	//Is the robot ready to shoot
	//The state of the Stop Motor (Lob or Shoot)
	int StopState;
	Timer timer;
	bool calibratedWithArm;
public:
	//Encoder* winchEncoder;
	Encoder* stopperEncoder;
	Encoder* armEncoder;
	
	//Encoder value for the Lob Position
	//Undetermined value #UNDETERMINED
	static const double STOP_LOB_POSITION = 0;
	//Encoder value for the Shoot Position
	//Undetermined value #UNDETERMINED
	static const double STOP_SHOOT_POSITION = 0;
	//StopState for the Stop motor in the Lob position
	static const int STOP_LOB = 0;
	//StopState for the Stop motor in the Shoot position
	static const int STOP_SHOOT = 1;
	StopperWinch();
	~StopperWinch();
	void InitDefaultCommand();
	void setStopperDirect(double speed);
	void ProjectSensors();
	void resetStopEncoder();
	//Get/set methods
	void setGoal(double angle);
	double getCatapultPosition();
	double getStopPosition();
	//double getWinchPosition();
	bool getReady();
	int getStopState();

	bool armSwitchState();
};

#endif

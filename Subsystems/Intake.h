/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Erin Duebner, James Li                                         */
/*-------------------------------------------------------------------------*/

#ifndef INTAKE_H
#define INTAKE_H
#include "../Logger/Logger.h"
#include "../Logger/LogSubsystem.h"
#include "WPILib.h"

class Intake: public LogSubsystem {
private:
	//motor that controls beater bar, the actual intake mechanism
	Talon* intake;
	//solenoid that controls position of beater bar
	Solenoid* extend;
	//solenoid that controls whether extend solenoid gets air
	Solenoid* idle;
	bool idleSet;
	bool extendSet;
	Timer readyTimer;
	Logger* log;
public:
	//encoder for beater bar
	Encoder* intakeEncoder;
	
	Intake();
	~Intake();
	void InitDefaultCommand();
	//sets the speed of the beater bar
	void BeaterBar(double speed);
	//takes a boolean and determines speed of beater bar
	//0 if false, some undetermined value if true
	void TakeBall(bool isOn);
	//sets state of idle solenoid
	void SetIdle(bool in);
	//sets state of extend solenoid
	void ExtendArms(bool extended);
	//gets speed of beater bar
	double getSpeed();
	//gets state of extend solenoid
	bool getExtend();
	//gets state of idle solenoid
	bool getIdle();
	//gets whether ready to shoot
	bool getReadyToShoot();
	//call at beginning of auto.
	void ResetIdleTimer();
};

#endif

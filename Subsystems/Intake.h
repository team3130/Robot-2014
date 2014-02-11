/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Erin Duebner, James Li                                         */
/*-------------------------------------------------------------------------*/

#ifndef INTAKE_H
#define INTAKE_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

class Intake: public Subsystem {
private:
	Jaguar* intake;
	Solenoid* extend;
	bool isExtend;
	bool isOn;
public:
	Encoder* intakeEncoder;
	
	Intake();
	Intake(int intakeChannel, int extendChannel);
	void InitDefaultCommand();
	void TakeBall();
	void ExtendArms();
};

#endif

/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li                                                       */
/*-------------------------------------------------------------------------*/

#ifndef INTAKE_H
#define INTAKE_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

class Intake: public Subsystem {
private:
	Jaguar* intake;
public:
	Encoder* intakeEncoder;
	
	Intake();
	Intake(int intakeChannel);
	void InitDefaultCommand();
};

#endif

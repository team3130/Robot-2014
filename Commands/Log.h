/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Matthew Ickstadt                                               */
/*-------------------------------------------------------------------------*/
#ifndef _LOG_H
#define _LOG_H

#include "../Robot.h"
#include "../Logger/Sensor.h"
#include <vector>
#include "semLib.h"

class Log : public Command {
	std::vector<Sensor<Encoder>* > *m_encoders;
	std::vector<Sensor<DigitalInput>* > *m_dis;
	std::vector<Sensor<Gyro>* > *m_gyros;
	SEM_ID Sensor_Mutex;
public:
	Log(std::vector<Sensor<Encoder>* > *encoders,
		std::vector<Sensor<DigitalInput>* > *dis,
		std::vector<Sensor<Gyro>* > *gyros, SEM_ID);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

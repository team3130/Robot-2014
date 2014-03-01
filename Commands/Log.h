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

class Log : public Command {
	std::vector<Sensor<Encoder, double>* > *m_encoders_d;
	std::vector<Sensor<Encoder, float>* > *m_encoders_f;
	std::vector<Sensor<DigitalInput, double>* > *m_dis;
	std::vector<Sensor<Gyro, double>* > *m_gyros;
public:
	Log(std::vector<Sensor<Encoder, double>* > *encoders_d,
		std::vector<Sensor<Encoder, float>* > *encoders_f,
		std::vector<Sensor<DigitalInput, double>* > *dis,
		std::vector<Sensor<Gyro, double>* > *gyros);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

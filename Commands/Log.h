/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Matthew Ickstadt                                               */
/*-------------------------------------------------------------------------*/
#ifndef _LOG_H
#define _LOG_H

#include "../Robot.h"

class Log : public Command {
	std::vector<Sensor_Types::encoder_sensor*> *m_encoders;
	std::vector<Sensor_Types::di_sensor*> *m_dis;
	std::vector<Sensor_Types::gyro_sensor*> *m_gyros;
public:
	Log(std::vector<Sensor_Types::encoder_sensor*> *encoders,
			std::vector<Sensor_Types::di_sensor*> *dis,
			std::vector<Sensor_Types::gyro_sensor*> *gyros);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

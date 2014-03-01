/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Matthew Ickstadt                                               */
/*-------------------------------------------------------------------------*/

#include "Log.h"
#include "../Subsystems/Logger.h"

Log::Log(std::vector<Sensor<Encoder>* > *encoders,
	std::vector<Sensor<DigitalInput>*> *dis,
	std::vector<Sensor<Gyro>*> *gyros, SEM_ID mutex)
	: m_encoders(encoders), m_dis(dis), m_gyros(gyros) {
		Requires(Robot::logger);
		Sensor_Mutex = mutex;
	}
	
void Log::Initialize() {
}

void Log::Execute() {
	semTake(Sensor_Mutex);
	std::vector<Sensor<Encoder>* >::iterator e_it;
	for (e_it = m_encoders->begin(); e_it != m_encoders->end(); ++e_it) {
		Robot::logger->update_number((*e_it)->m_name, (*e_it)->get());
	}
	std::vector<Sensor<DigitalInput,>* >::iterator d_it;
	for (d_it = m_dis->begin(); d_it != m_dis->end(); ++d_it) {
		Robot::logger->update_number((*d_it)->m_name, (*d_it)->get());
	}
	std::vector<Sensor<Gyro,>* >::iterator g_it;
	for (g_it = m_gyros->begin(); g_it != m_gyros->end(); ++g_it) {
		Robot::logger->update_number((*g_it)->m_name, (*g_it)->get());
	}
	semGive(Sensor_Mutex);
}
bool Log::IsFinished() {
	return false;
}
void Log::End() {

}
void Log::Interrupted() {
	End();
}

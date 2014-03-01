/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Matthew Ickstadt                                               */
/*-------------------------------------------------------------------------*/

#include "Log.h"
#include "../Subsystems/Logger.h"

Log::Log(std::vector<Sensor<Encoder, double>* > *encoders_d,
	std::vector<Sensor<Encoder, float>*> *encoders_f,
	std::vector<Sensor<DigitalInput, double>*> *dis,
	std::vector<Sensor<Gyro, float>*> *gyros)
	:
	m_encoders_d(encoders_d), m_encoders_f(encoders_f), m_dis(dis), m_gyros(gyros) {
		Requires(Robot::logger);
	}
	
void Log::Initialize() {
}

void Log::Execute() {
	std::vector<Sensor<Encoder, double>* >::iterator ed_it;
	for (ed_it = m_encoders_d->begin(); ed_it != m_encoders_d->end(); ++ed_it) {
		Robot::logger->update_number((*ed_it)->m_name, (*ed_it)->get());
	}
	std::vector<Sensor<Encoder, float>* >::iterator ef_it;
	for (ef_it = m_encoders_f->begin(); ef_it != m_encoders_f->end(); ++ef_it) {
		Robot::logger->update_number((*ef_it)->m_name, (*ef_it)->get());
	}
	std::vector<Sensor<DigitalInput, double>* >::iterator d_it;
	for (d_it = m_dis->begin(); d_it != m_dis->end(); ++d_it) {
		Robot::logger->update_number((*d_it)->m_name, (*d_it)->get());
	}
	std::vector<Sensor<Gyro, float>* >::iterator g_it;
	for (g_it = m_gyros->begin(); g_it != m_gyros->end(); ++g_it) {
		Robot::logger->update_number((*g_it)->m_name, (*g_it)->get());
	}
}
bool Log::IsFinished() {
	return false;
}
void Log::End() {

}
void Log::Interrupted() {
	End();
}

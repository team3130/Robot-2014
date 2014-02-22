/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Matthew Ickstadt                                               */
/*-------------------------------------------------------------------------*/

#include "Log.h"

Log::Log(const char* name) {
	Requires(logger);
}
void Log::Initialize() {

}
void Log::Execute() {
	for (logger->m_sensors::iterator it = logger->m_sensors.begin(); it != logger->m_sensors.end(); ++it) {
		logger->update_number((*it)->m_name, (*it)->Get());
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
/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Matthew Ickstadt                                               */
/*-------------------------------------------------------------------------*/
#include "Logger.h"
#include "../Commands/Log.h"
#include "Driverstation.h"
#include "stat.h"
#include <iostream>
#include <algorithm>
#include "tables/TableKeyNotDefinedException.h"
#include "semLib.h"

int file_exists (char *filename)
{
  struct stat buffer;   
  return (stat(filename, &buffer) == 0);
}


Logger::Logger() :
		Subsystem("Logger"),
		m_encoders(new std::vector<Sensor<Encoder>*>),
		m_dis(new std::vector<Sensor<DigitalInput>*>),
		m_gyros(new std::vector<Sensor<Gyro>*>),
		m_file(NULL),
		m_table(NULL)
		{
	// Remove old match data if present
	if (file_exists(LOG_FILE_OLD)) {
		remove(LOG_FILE_OLD);
	}
	
	// Rename match data to old match data if present
	if (file_exists(LOG_FILE)) {
		rename(LOG_FILE, LOG_FILE_OLD);
	}
	
	m_file = fopen(LOG_FILE, "w");
	
//	NetworkTable::SetTeam(3130);
//	NetworkTable::SetServerMode();
	m_table = NetworkTable::GetTable("log");

	Sensor_Mutex = semMInitialize(m_sem, 0);
}

Logger::~Logger() {
	delete m_encoders;
	delete m_dis;
	delete m_gyros;
	m_file = NULL;
	m_table = NULL;
}

void Logger::add_sensor(Sensor<Encoder>* s) {
	semTake(Sensor_Mutex, WAIT_FOREVER);
	m_encoders->push_back(s);
	semGive(Sensor_Mutex);
}
void Logger::add_sensor(Sensor<DigitalInput>* s) {
	semTake(Sensor_Mutex, WAIT_FOREVER);
	m_dis->push_back(s);
	semGive(Sensor_Mutex);
}
void Logger::add_sensor(Sensor<Gyro>* s) {
	semTake(Sensor_Mutex, WAIT_FOREVER);
	m_gyros->push_back(s);
	semGive(Sensor_Mutex);
}

void Logger::remove_sensor(Sensor<Encoder>* s) {
	semTake(Sensor_Mutex, WAIT_FOREVER);
	m_encoders->erase(std::remove(m_encoders->begin(), m_encoders->end(), s), m_encoders->end());
	semGive(Sensor_Mutex);
}
void Logger::remove_sensor(Sensor<DigitalInput>* s) {
	semTake(Sensor_Mutex, WAIT_FOREVER);
	m_dis->erase(std::remove(m_dis->begin(), m_dis->end(), s), m_dis->end());
	semGive(Sensor_Mutex);
}
void Logger::remove_sensor(Sensor<Gyro>* s) {
	semTake(Sensor_Mutex, WAIT_FOREVER);
	m_gyros->erase(std::remove(m_gyros->begin(), m_gyros->end(), s), m_gyros->end());
	semGive(Sensor_Mutex);
}

void Logger::update_number(const char* name, double value) {
	char buf[20];
	snprintf(buf, 20, "%f.4", DriverStation::GetInstance()->GetMatchTime());
	
	NetworkTable* subtable = m_table->GetSubTable(name);
	subtable->PutNumber(buf, value);
	
	fprintf(m_file, "N %s %f.10\n", name, value);
}

void Logger::update_string(const char* name, const char* value) {
	char buf[20];
	snprintf(buf, 20, "%f.4", DriverStation::GetInstance()->GetMatchTime());
	
	NetworkTable* subtable = m_table->GetSubTable(name);
	subtable->PutString(buf, value);
	
	fprintf(m_file, "S %s %s\n", name, value);
}

void Logger::update_bool(const char* name, bool value) {
	char buf[20];
	snprintf(buf, 20, "%f.4", DriverStation::GetInstance()->GetMatchTime());
	
	NetworkTable* subtable = m_table->GetSubTable(name);
	subtable->PutBoolean(buf, value);
	
	fprintf(m_file, "B %s %s\n", name, value ? "true" : "false");
}

// Only for doubles ...?
void Logger::ValueChanged(ITable* source, const std::string& key, EntryValue value, bool isNew) {
	std::string name;
	try {
		name = source->GetString("_TableName");
	} catch (TableKeyNotDefinedException* e) {
		std::cout << "ERROR" << e->what() << std::endl;
		return;
	}
	char buf[20];
	snprintf(buf, 20, "%f.4", DriverStation::GetInstance()->GetMatchTime());
	m_table->GetSubTable(name)->GetSubTable(key)->PutNumber(std::string(buf), value.f);
}

void Logger::InitDefaultCommand() {
	SetDefaultCommand(new Log(m_encoders, m_dis, m_gyros, Sensor_Mutex));
}





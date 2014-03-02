/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Matthew Ickstadt                                               */
/*-------------------------------------------------------------------------*/
#ifndef _LOGGER_H
#define _LOGGER_H

#include <cstdio>
#include <vector>
#include "WPILib.h"
#include "../Logger/Sensor.h"
#include "semLib.h"

#define LOG_FILE "match.log"
#define LOG_FILE_OLD "old_match.log"

class Logger : public Subsystem {
public:	
	
	void update_number(const char* name, double value);
	void update_string(const char* name, const char* value);
	void update_bool(const char* name, bool value);
	void ValueChanged(ITable* source, const std::string& key, EntryValue value, bool isNew); // Implements ITableListener
	void add_sensor(Sensor<Encoder>*);
	void add_sensor(Sensor<DigitalInput>*);
	void add_sensor(Sensor<Gyro>*);

	void remove_sensor(Sensor<Encoder>*);
	void remove_sensor(Sensor<DigitalInput>*);
	void remove_sensor(Sensor<Gyro>*);
	
	Logger();
	~Logger();

	void InitDefaultCommand();

	VX_MUTEX_SEMAPHORE(m_sem);
	SEM_ID Sensor_Mutex;
	
private:
	std::vector<Sensor<Encoder>* > *m_encoders;
	std::vector<Sensor<DigitalInput>* > *m_dis;
	std::vector<Sensor<Gyro>* > *m_gyros;
	
	FILE* m_file;
	NetworkTable* m_table;
};

#endif

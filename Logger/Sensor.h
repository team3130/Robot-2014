/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Matthew Ickstadt                                               */
/*-------------------------------------------------------------------------*/
#ifndef _SENSOR_H
#define _SENSOR_H

#include "GetSensor.h"
#include "../Subsystems/VelocityController.h"

// templates are useless becuase we don't have shared_ptr<>
class Sensor
{
private:
	const void *m_funcPtr;
	void *m_classPtr;
	const int m_t;
public:
	typedef double (*dfuncptr)();
	typedef float (*ffuncptr)();
	typedef int (*ifuncptr)();
	typedef bool (*bfuncptr)();
	static const int kDouble = 0;
	static const int kFloat = 1;
	static const int kInt = 2;
	static const int kBool = 3;
	const char* m_name;
	
	Sensor(const char* name, void* classptr, dfuncptr func);
	Sensor(const char* name, ifuncptr func);
	Sensor(const char* name, ffuncptr func);
	virtual ~Sensor();
	virtual double Get();
};

#endif

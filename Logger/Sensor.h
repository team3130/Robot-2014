/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Matthew Ickstadt                                               */
/*-------------------------------------------------------------------------*/
#ifndef _SENSOR_H
#define _SENSOR_H


// templates are useless becuase we don't have shared_ptr<>
class Sensor
{
private:
	typedef double (*dfuncptr)();
	typedef float (*ffuncptr)();
	typedef int (*ifuncptr)();
	const void *m_funcPtr;
	const int m_t;
public:
	static const int kDouble = 0;
	static const int kFloat = 1;
	static const int kInt = 2;
	const char* m_name;
	
	Sensor(dfuncptr func, const char* name);
	Sensor(ifuncptr func, const char* name);
	Sensor(ffuncptr func, const char* name);
	virtual ~Sensor();
	virtual double Get();
};

#endif

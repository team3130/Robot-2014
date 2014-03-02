/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Matthew Ickstadt                                               */
/*-------------------------------------------------------------------------*/
#ifndef _SENSOR_H
#define _SENSOR_H

static const int DOUBLE = 0;
static const int FLOAT = 1;

/**
 * C: The class type (non-pointer)

 * Example:
 *   Sensor<Encoder>
 * Encapsulates an Encoder object for any funciton that
 * returns a double or float.
 */
template<typename C>
class Sensor {
public:
	
	typedef double (C::*d_funcPtr_t)();
	typedef float (C::*f_funcPtr_t)();

	const char* m_name;
	const int m_sensorType;
	
private:
	C &m_classPtr;
	d_funcPtr_t d_funcPtr;
	f_funcPtr_t f_funcPtr;

public:
	
	Sensor(const char* name, C &classPtr, const int &type, d_funcPtr_t funcPtr) :
		m_name(name), m_sensorType(type), m_classPtr(classPtr), d_funcPtr(funcPtr), f_funcPtr(NULL) {
	}
	Sensor(const char* name, C &classPtr, const int &type, f_funcPtr_t funcPtr) :
		m_name(name), m_sensorType(type), m_classPtr(classPtr), d_funcPtr(NULL), f_funcPtr(funcPtr) {
	}

	inline double get() {
		switch (m_sensorType) {
		case DOUBLE:
			return (double)(m_classPtr.*d_funcPtr)();
		case FLOAT:
			return (double)(m_classPtr.*f_funcPtr)();
		}
		return 0.0;
	}
};

#endif

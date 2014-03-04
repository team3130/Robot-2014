/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Matthew Ickstadt                                               */
/*-------------------------------------------------------------------------*/
#ifndef _SENSOR_H
#define _SENSOR_H

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
	
	static const int DOUBLE = 0;
	static const int FLOAT = 1;
	static const int INT = 2;
	static const int BOOL = 3;
	
	typedef double (C::*d_funcPtr_t)();
	typedef float (C::*f_funcPtr_t)();
	typedef int (C::*i_funcPtr_t)();
	typedef bool (C::*b_funcPtr_t)();

	const char* m_name;
	const int m_sensorType;
	
private:
	C &m_classPtr;
	
	union funcPtr_t {
		d_funcPtr_t d;
		f_funcPtr_t f;
		i_funcPtr_t i;
		b_funcPtr_t b;
		
		funcPtr_t() : d(0) {}
		funcPtr_t(d_funcPtr_t _d) : d(_d) {}
		funcPtr_t(f_funcPtr_t _f) : f(_f) {}
		funcPtr_t(i_funcPtr_t _i) : i(_i) {}
		funcPtr_t(b_funcPtr_t THISISABOOL) : b(THISISABOOL) {} // Need weird name to avoid already declared symbols?
	} funcPtr;

public:
	
	Sensor(const char* name, C &classPtr, d_funcPtr_t funcPtr) :
		m_name(name), m_sensorType(DOUBLE), m_classPtr(classPtr), funcPtr(funcPtr) {
	}
	Sensor(const char* name, C &classPtr, f_funcPtr_t funcPtr) :
		m_name(name), m_sensorType(FLOAT), m_classPtr(classPtr), funcPtr(funcPtr) {
	}
	Sensor(const char* name, C &classPtr, i_funcPtr_t funcPtr) :
		m_name(name), m_sensorType(INT), m_classPtr(classPtr), funcPtr(funcPtr) {
	}
	Sensor(const char* name, C &classPtr, b_funcPtr_t funcPtr) :
		m_name(name), m_sensorType(BOOL), m_classPtr(classPtr), funcPtr(funcPtr) {
	}

	inline double get() {
		switch (m_sensorType) {
		case DOUBLE:
			return (double)(m_classPtr.*funcPtr.d)();
		case FLOAT:
			return (double)(m_classPtr.*funcPtr.f)();
		case INT:
			return (double)(m_classPtr.*funcPtr.i)();
		case BOOL:
			return (double)(m_classPtr.*funcPtr.b)();
		}
		return 0.0;
	}
};

#endif

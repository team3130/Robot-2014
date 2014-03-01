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
private:
	C *m_classPtr;
	void* m_funcPtr;

	typedef double (C::*d_funcptr_t)();
	typedef float (C::*f_funcptr_t)();
public:
	const int DOUBLE = 0;
	const int FLOAT = 1;

	const char* m_name;
	const int m_type;

	Sensor(const char* name, C* classPtr, int type, void* funcPtr) :
		m_name(name), m_classPtr(classPtr), m_type(type), m_funcPtr(funcPtr) {
	}

	inline double get() {
		switch m_type {
		case DOUBLE:
			return (double)(*m_classPtr.*(d_funcptr_t)m_funcPtr)();
		case FLOAT:
			return (double)(*m_classPtr.*(f_funcptr_t)m_funcPtr)();
		}
	}
};

#endif

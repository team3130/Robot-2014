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
 * F: The function return type
 * 
 * Example:
 *   Sensor<Encoder, double>
 * Encapsulates an Encoder object for any funciton that
 * returns a double.
 */
template<typename C, typename F>
class Sensor {
	// Pointer to Member function of C which returns an F
	typedef F (C::*funcptr_t)();
private:
	C *m_classPtr;
	funcptr_t m_funcPtr;
public:

	const char* m_name;

	Sensor(const char* name, C* classPtr, funcptr_t funcPtr) :
		m_name(name), m_classPtr(classPtr), m_funcPtr(funcPtr) {
	}

	inline double get() {
		return (double)(*m_classPtr.*m_funcPtr)();
	}
};

namespace Sensor_Types {
	typedef Sensor<Encoder, double> encoder_sensor;
	typedef Sensor<DigitalInput, double> di_sensor;
	typedef Sensor<Gyro, double> gyro_sensor;
}

#endif

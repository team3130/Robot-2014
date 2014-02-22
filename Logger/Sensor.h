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
	enum Type {
		Double;
		Int;
		Float;
	};
	const char* m_name;
private:
	void *m_funcPtr
	Type m_type;
public:
	Sensor(double (*func)(), const char* name) : m_funcPtr(func), m_type(Double), m_name(name) {}
	Sensor(int (*func)(), const char* name) : m_funcPtr(func), m_type(Int), m_name(name) {}
	Sensor(float (*func)(), const char* name) : m_funcPtr(func), m_type(Float), m_name(name) {}
	~Sensor() {
		m_funcPtrDouble = NULL;
		m_funcPtrFloat = NULL;
		m_funcPtrInt = NULL;
	virtual double Get() const = 0 {
		switch (m_type) {
		case Double:
			return double((double (*)m_funcPtr())());
			break;
		case Int:
			return double((int (*)m_funcPtr())());
			break;
		case Float:
			return double((float (*)m_funcPtr())());
			break;
		}
	}
};

#endif
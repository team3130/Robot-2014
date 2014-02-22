#include "Sensor.h"
#define NULL 0

Sensor::Sensor(double(*func)(), const char* name) :
	m_funcPtr((void*) func), m_t(kDouble), m_name(name) {
}
Sensor::Sensor(int(*func)(), const char* name) :
	m_funcPtr((void*) func), m_t(kInt), m_name(name) {
}
Sensor::Sensor(float(*func)(), const char* name) :
	m_funcPtr((void*) func), m_t(kFloat), m_name(name) {
}
Sensor::~Sensor() {
	m_funcPtr = NULL;
}
double Sensor::Get() {
	switch (m_t) {
		case kDouble:
		return double(((dfuncptr)m_funcPtr)());
		break;
		case kInt:
		return double(((ifuncptr)m_funcPtr)());
		break;
		case kFloat:
		return double(((ffuncptr)m_funcPtr)());
		break;
	}
	return 0.0;
}

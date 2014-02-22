#include "Sensor.h"

Sensor::Sensor(const char* name, void* classPtr, dfuncptr func) :
	m_funcPtr((void*) func), m_classPtr(classPtr), m_t(kDouble), m_name(name) {
}
Sensor::Sensor(const char* name, ifuncptr func) :
	m_funcPtr((void*) func), m_t(kInt), m_name(name) {
}
Sensor::Sensor(const char* name, ffuncptr func) :
	m_funcPtr((void*) func), m_t(kFloat), m_name(name) {
}
Sensor::~Sensor() {
}
double Sensor::Get() {
	switch (m_t) {
		case kDouble:
		GetSensorClassPtr = m_classPtr;
		return double(((dfuncptr)m_funcPtr)());
		break;
		case kInt:
		GetSensorClassPtr = m_classPtr;
		return double(((ifuncptr)m_funcPtr)());
		break;
		case kFloat:
		GetSensorClassPtr = m_classPtr;
		return double(((ffuncptr)m_funcPtr)());
		break;
	}
	return 0.0;
}

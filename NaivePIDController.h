#ifndef NPID_CONTROLLER
#define NPID_CONTROLLER

#include "WPILib.h"
#include "string.h"

class NaivePIDController{
public:
	float currentError;
	float setPoint;
	float P, I, D;
	float accum;
	long lastSetTime;
	float lastError;
	std::string name;
	NaivePIDController(string name);
	float update(float value, long time);
	void resetTime();
	void reset();
	void setSetPoint(float in);
	void set(float P, float I, float D);
private:
	Timer timer;
	void projectPIDValues();
	void getPIDValues();
};
#endif

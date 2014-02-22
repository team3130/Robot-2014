/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Matthew Ickstadt                                               */
/*-------------------------------------------------------------------------*/
#ifndef _GETSENSOR_H
#define _GETSENSOR_H

#include "WPILib.h"

static void* GetSensorClassPtr;

template<typename T>
class GetSensor {
public:	
	static inline double get() {
		return ((T*)(GetSensorClassPtr))->Get();
	}
	
	static inline double getAngle() {
		return ((T*)(GetSensorClassPtr))->GetAngle();
	}
	
	static inline double getRate() {
		return ((T*)(GetSensorClassPtr))->GetRate();
	}
	
	static inline double getRaw() {
		return ((T*)(GetSensorClassPtr))->GetRaw();
	}
	
	static inline double getEncoder() {
		return ((T*)(GetSensorClassPtr))->Encoder::Get();
	}
	
	static inline double getMotor() {
		return ((T*)(GetSensorClassPtr))->SpeedController::Get();
	}
	
	static inline double getDistance() {
		return ((T*)(GetSensorClassPtr))->GetDistance();
	}
	
};


#endif

/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Created on: Feb 6, 2014                                                 */
/* Authors: Mikhail Kyraha                                                 */
/*-------------------------------------------------------------------------*/
#ifndef VELOCITY_CONTROLLER_H
#define VELOCITY_CONTROLLER_H
//#include "Commands/Subsystem.h"
#include "WPILib.h"
//#include "string.h"

class VelocityController: public Talon, public Encoder {
private:
	double m_kP;
	double m_power;
	Talon* m_satellite;
	bool m_smart;
	bool m_invertOutput;
public:
	VelocityController(uint32_t channel, uint32_t sat_channel,
			uint32_t aChannel, uint32_t bChannel,
			Encoder::EncodingType encodingType = Encoder::k4X);
	~VelocityController();
	virtual void Set(float speed, uint8_t syncGroup=0);
	void UseEncoder(bool use=true) {m_smart = use;}
	void SetInvertedMotor(bool inverted);
};

#endif

/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Created on: Feb 6, 2014                                                 */
/* Authors: Mikhail Kyraha                                                 */
/*-------------------------------------------------------------------------*/

#include "VelocityController.h"

/**
 * @param channel The PWM channel on the digital module that the Jaguar is attached to.
 * @param aChannel Encoder's a channel digital input channel.
 * @param bChannel Encoder's b channel digital input channel.
 * @param reversedEncoder Indicates negative readings while positive power applied to the motor.
 * @param encodingType either k1X, k2X, or k4X. See Encoder class 
 *
 * @author M.Kyraha
 */
VelocityController::VelocityController(uint32_t channel, uint32_t aChannel, uint32_t bChannel,
		bool reversedEncoder, Encoder::EncodingType encodingType)
	: Jaguar(channel), Encoder(aChannel, bChannel, reversedEncoder, encodingType) {
	m_kP = 1;
	m_power = 0;
	m_smart = true;
}

void VelocityController::Set(float velocity, uint8_t syncGroup) {
	if(m_smart) {
		double delta = velocity - GetRate();
		m_power += m_kP * delta;
	}
	else {
		m_power = velocity;
	}
	Jaguar::Set(m_power,syncGroup);
}

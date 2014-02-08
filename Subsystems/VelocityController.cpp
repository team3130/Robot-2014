/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Created on: Feb 6, 2014                                                 */
/* Authors: Mikhail Kyraha                                                 */
/*-------------------------------------------------------------------------*/

#include "VelocityController.h"
#include "math.h"
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
	m_reversedEncoder=reversedEncoder;
	m_smartInvertOutput = false;
	SmartDashboard::PutNumber("VelocityController P",1000);
	SmartDashboard::PutNumber("VelocityController W",2);
}
VelocityController::~VelocityController(){
	
}
void VelocityController::SetSmartInvertedMotor(bool inverted){
	m_smartInvertOutput = inverted;
}
void VelocityController::Set(float velocity, uint8_t syncGroup) {
	static int skipWrite = 0;
	m_kP = SmartDashboard::GetNumber("VelocityController P")/1000.0;
	if(m_smart) {
		if(m_smartInvertOutput)velocity*=-1;
		double deltaAbs = fabs(velocity - GetRate());
		deltaAbs = pow(deltaAbs, SmartDashboard::GetNumber("VelocityController W"));
		double correctAmount= m_kP * deltaAbs;
		if(velocity>GetRate())
			m_power += correctAmount;
		else
			m_power -= correctAmount;
		if(skipWrite%2==0){
			SmartDashboard::PutNumber("VelocityController Power 0", m_power);
			SmartDashboard::PutNumber("VelocityController DeltaAbs 0", deltaAbs);
			SmartDashboard::PutNumber("VelocityController Delta 0", (velocity-GetRate()));
		}
		if(skipWrite%2==1){
			SmartDashboard::PutNumber("VelocityController Power 1", m_power);
			SmartDashboard::PutNumber("VelocityController DeltaAbs 1", deltaAbs);
			SmartDashboard::PutNumber("VelocityController Delta 1", (velocity-GetRate()));
		}
	}
	else {
		m_power = velocity;
	}
	if(velocity==0)m_power=0;	//when we tell the motor to stop, do not delay the stop by waiting for our controller to catch up.
	if(m_smart && m_smartInvertOutput){
		Jaguar::Set(-m_power,syncGroup);
	}
	else Jaguar::Set(m_power,syncGroup);
	skipWrite++;
}

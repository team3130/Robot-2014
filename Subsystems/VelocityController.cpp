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
 * @param channel The PWM channel on the digital module that the Talon is attached to.
 * @param sat_channel The PWM channel that the satellite (seccond) Talon is attached to.
 * @param aChannel Encoder's a channel digital input channel.
 * @param bChannel Encoder's b channel digital input channel.
 * @param encodingType either k1X, k2X, or k4X. See Encoder class 
 *
 * @author M.Kyraha
 */
VelocityController::VelocityController(const char *name, uint32_t channel, uint32_t sat_channel,
		uint32_t aChannel, uint32_t bChannel, Encoder::EncodingType encodingType)
	: Talon(channel), Encoder(aChannel, bChannel, false, encodingType), m_name(name) {
	m_satellite = new Talon(sat_channel);
	m_kP = 1;
	m_power = 0;
	m_smart = true;
	m_invertOutput = false;
	m_topSpeed = Robot::preferences->GetDouble("Low Gear Top Speed",150);
	Encoder::Start();
	SmartDashboard::PutNumber("VelocityController P",1000);
}
VelocityController::~VelocityController(){
	delete m_satellite;
}
void VelocityController::SetInvertedMotor(bool inverted){
	m_invertOutput = inverted;
}
void VelocityController::Set(float velocity, uint8_t syncGroup) {
	m_kP = SmartDashboard::GetNumber("VelocityController P")/1000.0;
	if(m_smart && velocity != 0) {
		double rate = GetRate() / m_topSpeed;
		double delta = fabs(velocity - rate);
		double increment = m_kP * pow(delta, fabs(rate)+1);

		if(velocity > rate) m_power += increment;
		else m_power -= increment;

		if(m_power>1.0) m_power = 1.0;
		if(m_power<-1.0) m_power = -1.0;

		SmartDashboard::PutNumber(std::string(m_name)+" VelocityController Power", m_power);
		SmartDashboard::PutNumber(std::string(m_name)+" VelocityController Delta", delta);
		SmartDashboard::PutNumber(std::string(m_name)+" VelocityController Increment", increment);
		SmartDashboard::PutNumber(std::string(m_name)+" VelocityController Velocity", velocity);
		SmartDashboard::PutNumber(std::string(m_name)+" VelocityController Rate", rate);
	}
	else {
		m_power = velocity;
	}

	if(m_invertOutput){
		Talon::Set(-m_power,syncGroup);
		m_satellite->Set(-m_power,syncGroup);
	}
	else {
		Talon::Set(m_power,syncGroup);
		m_satellite->Set(m_power,syncGroup);
	}
}

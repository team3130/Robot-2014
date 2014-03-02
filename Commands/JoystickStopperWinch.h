/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li                                                       */
/*-------------------------------------------------------------------------*/

#ifndef JOYSTICK_STOPPERWINCH_H
#define JOYSTICK_STOPPERWINCH_H

#include "../CommandBase.h"
#include "WPILib.h"

class JoystickStopperWinch: public CommandBase {
public:
	typedef enum {stopLow, stopHigh} PositionType;
	JoystickStopperWinch();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
private:
	bool m_manual;
	PositionType m_position;
};

#endif

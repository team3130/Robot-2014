/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: James Li                                                       */
/*-------------------------------------------------------------------------*/

#include "ShootCycle.h"
#include "math.h"

ShootCycle::ShootCycle() {
	shoot = new ShootCatapult();
	reset = new ResetCatapult();
	wind = new WindCatapult();
	AddSequential(reset);
	AddSequential(wind);
	AddSequential(shoot);
}

ShootCycle::~ShootCycle() {
	delete shoot;
	delete reset;
	delete wind;
}

void ShootCycle::Initialize()
{
	wind->ResetArm();
	reset->Initialize();
	shoot->Initialize();
}

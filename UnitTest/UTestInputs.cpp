/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Mikhail Kyraha                                                 */
/*-------------------------------------------------------------------------*/

#include "UTestInputs.h"
#include <sstream>

/* This command does nothing, only reads inputs and sends them to the SmartDashboard
 * To use this diagnostics tool an instance of this class needs to be created
 * Then put the instance on the SmartDashboard to have a "start"/"cancel" button
 */ 
UTestInputs::UTestInputs() : Command("UTest Sensors")
{
	SmartDashboard::PutData(this);
}

UTestInputs::~UTestInputs()
{
}

void UTestInputs::Initialize()
{
	for(int i=0;i<14;i++){
		m_inputs.push_back(new DigitalInput(i+1));
	}
}

void UTestInputs::Execute()
{
	vector<DigitalInput*>::iterator it = m_inputs.begin();
	int i = 0;
	while( it != m_inputs.end()) {
		std::ostringstream s;
		s << "Digital Input " << i;
		SmartDashboard::PutNumber(s.str(), (*it)->Get());
		++it;
		++i;
	}
}

bool UTestInputs::IsFinished(){
	return false;
}

void UTestInputs::End(){}
void UTestInputs::Interrupted(){}


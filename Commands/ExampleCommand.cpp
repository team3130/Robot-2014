/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: <INSERT AUTHOR(S) OF CODE>                                     */
/*-------------------------------------------------------------------------*/

#include "ExampleCommand.h"

ExampleCommand::ExampleCommand() {
	// Use Requires() here to declare subsystem dependencies
	//Requires(chassis);
}

// Called just before this Command runs the first time
void ExampleCommand::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void ExampleCommand::Execute() {
	char count='a';
	char bn[] = "JButton X  ";
	for(int i=0;i<14;i++){
		bn[9]=count;
		SmartDashboard::PutNumber(std::string(bn), oi->gamepad->GetRawButton(i));
		count++;
	}
	count='a';
	char an[]= "JAxis X  ";
	for(int i=0;i<10;i++){
		an[6]=count;
		SmartDashboard::PutNumber(std::string(an), oi->gamepad->GetRawAxis(i));
		count++;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ExampleCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ExampleCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ExampleCommand::Interrupted() {
}

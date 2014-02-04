/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty, Mikhail Kyraha                                  */
/*-------------------------------------------------------------------------*/
#include "../Robotmap.h"
#include "../Commands/JoystickTank.h"
#include "../Commands/JoystickStraight.h"
#include "Chassis.h"
#include "math.h"
#include "string.h"

Chassis::Chassis(int leftMotorChannel, int rightMotorChannel, int winchMotorChannel)
		: Subsystem("Chassis"){
	rightEncoder = new Encoder(C_ENCODER_RIGHT_CHANNEL_1,C_ENCODER_RIGHT_CHANNEL_2, false); 
	leftEncoder = new Encoder(C_ENCODER_LEFT_CHANNEL_1,C_ENCODER_LEFT_CHANNEL_2, true);
	winchEncoder = new Encoder(C_ENCODER_WINCH_CHANNEL_1, C_ENCODER_WINCH_CHANNEL_2, false);
	left = new Jaguar(leftMotorChannel);
	right = new Jaguar(rightMotorChannel);
	winch = new Jaguar(winchMotorChannel);
	drive=new RobotDrive(left, right);
	drive->SetInvertedMotor(RobotDrive::kRearLeftMotor,true);
	drive->SetInvertedMotor(RobotDrive::kRearRightMotor,true);
	
	bias = 0;
	drive->SetSafetyEnabled(false);
	//Assuming we have 4" (.1016m) wheels, pi*d = 3.14*.1016 = 0.319185meters per rotation
	//360 pulses per rotation -> 0.319185/360 = 0.0008866m/pulse.
	SmartDashboard::PutNumber("Encoder Distance (m) per Pulse", 0.0008866);
	SmartDashboard::PutNumber("Bias Multiplier",1000.0);
}
void Chassis::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new JoystickTank());
}
void Chassis::resetBias(){
	bias=0;
}
void Chassis::tankDrive(float leftSpeed, float rightSpeed){
	drive->TankDrive(leftSpeed, rightSpeed, false);
}
void Chassis::arcadeDrive(float move, float turn){
	drive->ArcadeDrive(move, turn, false);
}
void Chassis::straightDrive(float speed){
	double distPerPulse = SmartDashboard::GetNumber("Encoder Distance (m) per Pulse");
	leftEncoder->SetDistancePerPulse(distPerPulse);
	rightEncoder->SetDistancePerPulse(distPerPulse);

	if(speed<-1)speed=-1;
	if(speed>1)speed=1;
	double leftVelocity = leftEncoder->GetRate();
	double rightVelocity = rightEncoder->GetRate();
	double error= (fabs(rightVelocity)-fabs(leftVelocity));
	bias-=error*SmartDashboard::GetNumber("Bias Multiplier")/1000.0;
	//if(count++%3==0){
		SmartDashboard::PutNumber("Chassis Speed",speed);
		SmartDashboard::PutNumber("Chassis Bias", bias);
		SmartDashboard::PutNumber("Chassis Error", error);
		SmartDashboard::PutNumber("Chassis Left Velocity", leftVelocity);
		SmartDashboard::PutNumber("Chassis Right Velocity", rightVelocity);
	//}
	tankDrive(speed*(1.0-bias),speed*(1.0+bias));
}
void Chassis::adjustCatapult(double level){
	//double catapultPosition = winchEncoder->GetDistance();
	//catapultPosition += level;
}

#include "../Robotmap.h"
#include "../Commands/JoystickTank.h"
#include "../Commands/JoystickStraight.h"
#include "Chassis.h"
#include "math.h"
#include "string.h"

Chassis::Chassis(int leftMotorChannel, int rightMotorChannel)
		: Subsystem("Chassis"){
	rightEncoder = new Encoder(C_ENCODER_RIGHT_CHANNEL_1,C_ENCODER_RIGHT_CHANNEL_2, false); 
	leftEncoder = new Encoder(C_ENCODER_LEFT_CHANNEL_1,C_ENCODER_LEFT_CHANNEL_2, true);
	leftEncoder->SetDistancePerPulse(1);
	rightEncoder->SetDistancePerPulse(1);
	left = new Jaguar(leftMotorChannel);
	right = new Jaguar(rightMotorChannel);
	drive=new RobotDrive(left, right);
	drive->SetInvertedMotor(RobotDrive::kRearLeftMotor,true);
	drive->SetInvertedMotor(RobotDrive::kRearRightMotor,true);
	
	bias = 0;
	drive->SetSafetyEnabled(false);
	SmartDashboard::PutNumber("Bias Multiplier",1.0);
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

	if(speed<-1)speed=-1;
	if(speed>1)speed=1;
	leftEncoder->SetDistancePerPulse(.01);
	rightEncoder->SetDistancePerPulse(.01);
	double leftVelocity = leftEncoder->GetRate();
	double rightVelocity = rightEncoder->GetRate();
	double error= (fabs(rightVelocity)-fabs(leftVelocity));
	bias-=error*SmartDashboard::GetNumber("Bias Multiplier")/1000.0;
	//if(count++%3==0){
		SmartDashboard::PutNumber("Speed",speed);
		SmartDashboard::PutNumber("Bias", bias);
		SmartDashboard::PutNumber("Error", error);
		SmartDashboard::PutNumber("left", leftVelocity);
		SmartDashboard::PutNumber("right", rightVelocity);
	//}
	tankDrive(speed*(1.0-bias),speed*(1.0+bias));
}

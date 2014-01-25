#include "../Robotmap.h"
#include "../Commands/JoystickArcade.h"
#include "Chassis.h"
#include "math.h"
#include "string.h"

Chassis::Chassis(int leftMotorChannel, int rightMotorChannel)
		: Subsystem("Chassis"){
	rightEncoder = new Encoder(C_ENCODER_RIGHT_CHANNEL_1,C_ENCODER_RIGHT_CHANNEL_1); 
	leftEncoder = new Encoder(C_ENCODER_LEFT_CHANNEL_1,C_ENCODER_LEFT_CHANNEL_2, true);
	leftEncoder->SetDistancePerPulse(1);
	rightEncoder->SetDistancePerPulse(1);
	left = new Jaguar(leftMotorChannel);
	right = new Jaguar(rightMotorChannel);
	drive=new RobotDrive(left, right);
	drive->SetSafetyEnabled(false);
}
void Chassis::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new JoystickArcade());
}
void Chassis::tankDrive(float leftSpeed, float rightSpeed){
	drive->TankDrive(leftSpeed, rightSpeed, false);
}
void Chassis::arcadeDrive(float move, float turn){
	drive->ArcadeDrive(move, turn, false);
}

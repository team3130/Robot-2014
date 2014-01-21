#include "../Robotmap.h"
#include "../Commands/JoystickTank.h"
#include "Chassis.h"
#include "math.h"
#include "string.h"

Chassis::Chassis(int leftMotorChannel, int rightMotorChannel)
		: Subsystem("Chassis"), leftpc("Chassis Left Position"), rightpc("Chassis Right Position")
			, leftvc("Chassis Left Velocity"), rightvc("Chassis Right Velocity"){
	rightEncoder = new Encoder(C_ENCODER_RIGHT_CHANNEL_1,C_ENCODER_RIGHT_CHANNEL_1); 
	leftEncoder = new Encoder(C_ENCODER_LEFT_CHANNEL_1,C_ENCODER_LEFT_CHANNEL_2, true);
	left = new Jaguar(leftMotorChannel);
	right = new Jaguar(rightMotorChannel);
	drive=new RobotDrive(left, right);
	drive->SetSafetyEnabled(false);
}
void Chassis::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new JoystickTank());
}
void Chassis::tankDrive(float leftSpeed, float rightSpeed){
	drive->TankDrive(leftSpeed, rightSpeed, false);
}

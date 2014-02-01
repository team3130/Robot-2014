#include "EncoderRobotDrive.h"

EncoderRobotDrive::EncoderRobotDrive(
		SpeedController* leftController, SpeedController* rightController,
		Encoder* leftEncoder, Encoder* rightEncoder)
	: RobotDrive(leftController, rightController)
{
	leftPID = new PIDController(1.0,0.0,0.0,leftEncoder,leftController);
	rightPID = new PIDController(1.0,0.0,0.0,rightEncoder,rightController);
}
EncoderRobotDrive::~EncoderRobotDrive()
{
	delete leftPID;
	delete rightPID;
}
void EncoderRobotDrive::SetLeftRightMotorOutputs(float left, float right){
	RobotDrive::SetLeftRightMotorOutputs(left, right);
}

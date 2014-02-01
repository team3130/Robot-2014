#include "EncoderRobotDrive.h"

EncoderRobotDrive::EncoderRobotDrive(SpeedController* left, SpeedController* right) : RobotDrive(left,right){
	
}
void EncoderRobotDrive::SetLeftRightMotorOutputs(float left, float right){
	RobotDrive::SetLeftRightMotorOutputs(left, right);
}

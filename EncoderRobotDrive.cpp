#include "EncoderRobotDrive.h"

EncoderRobotDrive::EncoderRobotDrive (
		SpeedController* leftController, SpeedController* rightController,
		Encoder* leftEncoder, Encoder* rightEncoder)
	: RobotDrive(leftController, rightController)
{
	leftPID = new PIDController(0,0,0,leftEncoder,leftController);
	rightPID = new PIDController(0,0,0,rightEncoder,rightController);
	SmartDashboard::PutNumber("Smart Robot P", 0);
	SmartDashboard::PutNumber("Smart Robot I", 1);
	SmartDashboard::PutNumber("Smart Robot D", 0);
}

EncoderRobotDrive::~EncoderRobotDrive()
{
	delete leftPID;
	delete rightPID;
}

void EncoderRobotDrive::DumbRobot() {
	leftPID->Disable();
	rightPID->Disable();
	isBypass = true;
}

void EncoderRobotDrive::SmartRobot() {
	updatePIDValues(
		SmartDashboard::GetNumber("Smart Robot P"),
		SmartDashboard::GetNumber("Smart Robot I"),
		SmartDashboard::GetNumber("Smart Robot D"));
	leftPID->Enable();
	rightPID->Enable();
	isBypass = false;
}

void EncoderRobotDrive::updatePIDValues(double p, double i, double d){
	leftPID->SetPID(p,i,d);
	rightPID->SetPID(p,i,d);
	leftPID->Reset();
	rightPID->Reset();
}

void EncoderRobotDrive::SetLeftRightMotorOutputs(float left, float right){
	if(isBypass) {
		RobotDrive::SetLeftRightMotorOutputs(left, right);
	}
	else {
		leftPID->SetSetpoint(left);
		rightPID->SetSetpoint(right);
		SmartDashboard::PutNumber("Smart Robot Left Speed",left);
		SmartDashboard::PutNumber("Smart Robot Right Speed",right);
		SmartDashboard::PutNumber("Smart Robot Left PID output",leftPID->Get());
		SmartDashboard::PutNumber("Smart Robot Right PID output",rightPID->Get());
	}
}

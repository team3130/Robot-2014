#include "EncoderRobotDrive.h"

EncoderRobotDrive::EncoderRobotDrive(
		SpeedController* leftController, SpeedController* rightController,
		Encoder* leftEncoder, Encoder* rightEncoder)
	: RobotDrive(leftController, rightController)
{
	leftPID = new PIDController(0.0,1.0,0.0,leftEncoder,leftController);
	rightPID = new PIDController(0.0,1.0,0.0,rightEncoder,rightController);
}

EncoderRobotDrive::~EncoderRobotDrive()
{
	delete leftPID;
	delete rightPID;
}

void EncoderRobotDrive::DumbRobot(bool dumb) {
	if(dumb) {
		leftPID->Disable();
		rightPID->Disable();
		isBypass = true;
	}
	else {
		leftPID->Enable();
		rightPID->Enable();
		updatePIDValues(0,1,0);
		isBypass = false;
	}
}

void EncoderRobotDrive::updatePIDValues(double p, double i, double d){
	SmartDashboard::PutNumber("Smart Robot P",p);
	SmartDashboard::PutNumber("Smart Robot I",i);
	SmartDashboard::PutNumber("Smart Robot D",d);
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

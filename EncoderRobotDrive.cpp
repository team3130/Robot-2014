#include "EncoderRobotDrive.h"

EncoderRobotDrive::EncoderRobotDrive(
		SpeedController* leftController, SpeedController* rightController,
		Encoder* leftEncoder, Encoder* rightEncoder)
	: RobotDrive(leftController, rightController)
{
	leftPID = new PIDController(0.0,1.0,0.0,leftEncoder,leftController);
	rightPID = new PIDController(0.0,1.0,0.0,rightEncoder,rightController);
	leftPID->Enable();
	rightPID->Enable();
	projectPIDValues();
}
EncoderRobotDrive::~EncoderRobotDrive()
{
	delete leftPID;
	delete rightPID;
}
void EncoderRobotDrive::updatePIDValues(){
	getPIDValues();
	projectPIDValues();
	leftPID->Reset();
	rightPID->Reset();
}
void EncoderRobotDrive::SetLeftRightMotorOutputs(float left, float right){
	leftPID->SetSetpoint(left);
	rightPID->SetSetpoint(right);
	RobotDrive::SetLeftRightMotorOutputs(left, right);
	std::string name="Chassis Left";
	std::string namer="Chassis Right";
	//SmartDashboard::PutNumber("Left PID", leftPID->Get());
	//SmartDashboard::PutNumber("Right PID", rightPID->Get());
	//SmartDashboard::PutNumber("Left Error",this->leftPID->GetError());
	//SmartDashboard::PutNumber("Right Error",this->rightPID->GetError());
}
void EncoderRobotDrive::projectPIDValues(){
	std::string name="Chassis Left";
	//SmartDashboard::PutNumber(name+std::string(" P"),this->leftPID->GetP()*1000.);
	//SmartDashboard::PutNumber(name+std::string(" I"),this->leftPID->GetI()*1000.);
	//SmartDashboard::PutNumber(name+std::string(" D"),this->leftPID->GetD()*1000.);
	std::string namer="Chassis Right";
	//SmartDashboard::PutNumber(namer+std::string(" P"),this->rightPID->GetP()*1000.);
	//SmartDashboard::PutNumber(namer+std::string(" I"),this->rightPID->GetI()*1000.);
	//SmartDashboard::PutNumber(namer+std::string(" D"),this->rightPID->GetD()*1000.);
}
void EncoderRobotDrive::getPIDValues(){
	std::string name="Chassis Left";
	double P,I,D;
	P = SmartDashboard::GetNumber(name+std::string(" P"))/1000.;
	I = SmartDashboard::GetNumber(name+std::string(" I"))/1000.;
	D = SmartDashboard::GetNumber(name+std::string(" D"))/1000.;
	leftPID->SetPID(P,I,D);
	std::string namer="Chassis Right";
	P = SmartDashboard::GetNumber(namer+std::string(" P"))/1000.;
	I = SmartDashboard::GetNumber(namer+std::string(" I"))/1000.;
	D = SmartDashboard::GetNumber(namer+std::string(" D"))/1000.;
	rightPID->SetPID(P,I,D);
}

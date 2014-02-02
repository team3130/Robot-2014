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
	rightEncoder->SetPIDSourceParameter(PIDSource::kRate);
	leftEncoder->SetPIDSourceParameter(PIDSource::kRate);
	leftController = new Jaguar(leftMotorChannel);
	rightController = new Jaguar(rightMotorChannel);
	drive=new EncoderRobotDrive(leftController, rightController, leftEncoder, rightEncoder);
	drive->SetInvertedMotor(RobotDrive::kRearLeftMotor,true);
	drive->SetInvertedMotor(RobotDrive::kRearRightMotor,true);
	gyro = new Gyro(1);
	bias = 0;
	drive->SetSafetyEnabled(false);
	//Assuming we have 4" (.1016m) wheels, pi*d = 3.14*.1016 = 0.319185meters per rotation
	//360 pulses per rotation -> 0.319185/360 = 0.0008866m/pulse.
	//SmartDashboard::PutNumber("Encoder Distance (m) per Pulse", 0.0008866);
	//SmartDashboard::PutNumber("Bias Multiplier",1000.0);
	//SmartDashboard::PutNumber("Speed Multiplier",720);
	SmartDashboard::PutNumber("Pulses Per Distance",3000);
}
Chassis::~Chassis()
{
	delete rightEncoder;
	delete leftEncoder;
	delete leftController;
	delete rightController;
	delete drive;
	delete gyro;
}
void Chassis::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new JoystickTank());
}
void Chassis::resetBias(){
	bias=0;
}
void update(){
	
}
void Chassis::tankDrive(float leftSpeed, float rightSpeed){
	double ppd=SmartDashboard::GetNumber("Pulses Per Distance");	//# pulses per distance per second at maximum speed
	leftEncoder->SetDistancePerPulse(1.0/ppd);
	rightEncoder->SetDistancePerPulse(1.0/ppd);
	drive->TankDrive(leftSpeed, rightSpeed, false);

	SmartDashboard::PutNumber("Gyro Angle", gyro->GetAngle());
	SmartDashboard::PutNumber("Gyro Rate", gyro->GetRate());
	double leftVelocity = leftEncoder->GetRate();
	double rightVelocity = rightEncoder->GetRate();
	SmartDashboard::PutNumber("Chassis Left Velocity", leftVelocity);
	SmartDashboard::PutNumber("Chassis Right Velocity", rightVelocity);
}
void Chassis::arcadeDrive(float move, float turn){
	double ppd=SmartDashboard::GetNumber("Pulses Per Distance");	//# pulses per distance per second at maximum speed
	leftEncoder->SetDistancePerPulse(1.0/ppd);
	rightEncoder->SetDistancePerPulse(1.0/ppd);
	drive->ArcadeDrive(move, turn, false);
	
	SmartDashboard::PutNumber("Gyro Angle", gyro->GetAngle());
	SmartDashboard::PutNumber("Gyro Rate", gyro->GetRate());
	double leftVelocity = leftEncoder->GetRate();
	double rightVelocity = rightEncoder->GetRate();
	SmartDashboard::PutNumber("Chassis Left Velocity", leftVelocity);
	SmartDashboard::PutNumber("Chassis Right Velocity", rightVelocity);
}
void Chassis::straightDrive(float speed){

	if(speed<-1)speed=-1;
	if(speed>1)speed=1;
	double leftVelocity = leftEncoder->GetRate();
	double rightVelocity = rightEncoder->GetRate();
	double error= (fabs(rightVelocity)-fabs(leftVelocity));
	//error*=sign(rightVelocity)*sign(leftVelocity);
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

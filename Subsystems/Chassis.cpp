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

	SmartDashboard::PutNumber("Pulses Per Distance",Chassis::ENCODER_TOP_SPEED);
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
	double ppd=Chassis::ENCODER_TOP_SPEED;	//# pulses per distance per second at maximum speed
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
	double ppd=Chassis::ENCODER_TOP_SPEED;	//# pulses per distance per second at maximum speed
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

double Chassis::encoderUnitsToFeet(double in){
	static double conversionFactor = (Chassis::ENCODER_TOP_SPEED/360)*WHEEL_RADIUS_INCHES*WHEEL_RADIUS_INCHES*3.141592654/12;
	//1 EncoderUnit is defined as the maximum number of ticks counted by one encoder, for one drive motor, in one second, at maximum robot voltage.
	return in*conversionFactor;
}
double Chassis::feetToEncoderUnits(double in){
	static double conversionFactor = (Chassis::ENCODER_TOP_SPEED/360)*WHEEL_RADIUS_INCHES*WHEEL_RADIUS_INCHES*3.141592654/12;
	//1 EncoderUnit is defined as the maximum number of ticks counted by one encoder, for one drive motor, in one second, at maximum robot voltage.
	return in/conversionFactor;
}

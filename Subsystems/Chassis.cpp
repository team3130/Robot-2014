#include "../Robotmap.h"
#include "../Commands/JoystickTank.h"
#include "../Commands/JoystickStraight.h"
#include "Chassis.h"
#include "math.h"
#include "string.h"

Chassis::Chassis() : Subsystem("Chassis"){
	leftController = new Jaguar(C_LEFTMOTOR1);
	rightController = new Jaguar(C_RIGHTMOTOR1);
	rightEncoder = new Encoder(C_ENCODER_RIGHT_CHANNEL_1,C_ENCODER_RIGHT_CHANNEL_2, false); 
	leftEncoder = new Encoder(C_ENCODER_LEFT_CHANNEL_1,C_ENCODER_LEFT_CHANNEL_2, true);
	gyro = new Gyro(1);
	drive=new EncoderRobotDrive(leftController, rightController, leftEncoder, rightEncoder);
	drive->SetInvertedMotor(RobotDrive::kRearLeftMotor,true);
	drive->SetInvertedMotor(RobotDrive::kRearRightMotor,true);
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

void Chassis::tankDrive(float leftSpeed, float rightSpeed){
	drive->TankDrive(leftSpeed, rightSpeed, false);
	ProjectSensors();
}
void Chassis::arcadeDrive(float move, float turn){
	drive->ArcadeDrive(move, turn, false);
	ProjectSensors();
}

void Chassis::ProjectSensors() {
	SmartDashboard::PutNumber("Chassis Gyro Angle", gyro->GetAngle());
	SmartDashboard::PutNumber("Chassis Gyro Rate", gyro->GetRate());
	SmartDashboard::PutNumber("Chassis Left Velocity", leftEncoder->GetRate());
	SmartDashboard::PutNumber("Chassis Right Velocity", rightEncoder->GetRate());
	SmartDashboard::PutNumber("Encoder Left Raw",leftEncoder->GetRaw());
	SmartDashboard::PutNumber("Encoder Right Raw",rightEncoder->GetRaw());
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

/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty, Mikhail Kyraha                                  */
/*-------------------------------------------------------------------------*/
#include "../Robotmap.h"
#include "../Commands/JoystickTank.h"
#include "../Commands/JoystickStraight.h"
#include "Chassis.h"
#include "math.h"
#include "string.h"

Chassis::Chassis() : Subsystem("Chassis"){
	leftController = new VelocityController(C_LEFTMOTOR,C_LEFTSATELLITE,C_ENCODER_LEFT_A,C_ENCODER_LEFT_B, true);
	rightController = new VelocityController(C_RIGHTMOTOR,C_RIGHTSATELLITE,C_ENCODER_RIGHT_A,C_ENCODER_RIGHT_B, false);
	rightController->SetSmartInvertedMotor(true);
	//leftController->SetInverted(true);
	gyro  = new Gyro(C_GYRO);
	drive = new RobotDrive(leftController, rightController);
	drive->SetInvertedMotor(RobotDrive::kRearLeftMotor,true);
	drive->SetInvertedMotor(RobotDrive::kRearRightMotor,true);
	drive->SetSafetyEnabled(false);
	SmartDashboard::PutNumber("Pulses Per Distance",Chassis::ENCODER_TOP_SPEED);
}

Chassis::~Chassis()
{
	delete leftController;
	delete rightController;
	delete drive;
	delete gyro;
}

void Chassis::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new JoystickTank());
}

void Chassis::InitEncoders() {
	leftController->SetDistancePerPulse(1.0/ENCODER_TOP_SPEED);
	rightController->SetDistancePerPulse(1.0/ENCODER_TOP_SPEED);
	leftController->Reset();
	rightController->Reset();
	leftController->Start();
	rightController->Start();
}

double Chassis::GetDistance() {
	return (leftController->GetDistance()+rightController->GetDistance())/2.0;
}

void Chassis::tankDrive(float leftSpeed, float rightSpeed){
	drive->TankDrive(leftSpeed, rightSpeed, false);
	ProjectSensors();
}
void Chassis::arcadeDrive(float move, float turn){
	drive->ArcadeDrive(move, turn, false);
	ProjectSensors();
}

void Chassis::SmartRobot(bool smart) {
	leftController->UseEncoder(smart);
	rightController->UseEncoder(smart);
}

void Chassis::ProjectSensors() {
	SmartDashboard::PutNumber("Chassis Gyro Angle", gyro->GetAngle());
	SmartDashboard::PutNumber("Chassis Gyro Rate",  gyro->GetRate());
	SmartDashboard::PutNumber("Chassis Left  Raw",      leftController->Encoder::GetRaw());
	SmartDashboard::PutNumber("Chassis Right Raw",      rightController->Encoder::GetRaw());
	SmartDashboard::PutNumber("Chassis Left  Velocity", leftController->GetRate());
	SmartDashboard::PutNumber("Chassis Right Velocity", rightController->GetRate());
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

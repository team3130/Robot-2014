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
	isUsingEncoders = false;
	isUsingGyro = false;
	leftController = new VelocityController(C_LEFTMOTOR,C_LEFTSATELLITE,C_ENCODER_LEFT_A,C_ENCODER_LEFT_B);
	rightController = new VelocityController(C_RIGHTMOTOR,C_RIGHTSATELLITE,C_ENCODER_RIGHT_A,C_ENCODER_RIGHT_B);
	shifter = new Solenoid(C_SHIFTER);
	gyro  = new Gyro(C_GYRO);
	drive = new RobotDrive(leftController, rightController);
	// Never use RobotDrive's SetInvertedMotor, use VelocityConltroller's one instead
	drive->SetSafetyEnabled(false);
	leftController->SetInvertedMotor(true);
	rightController->SetInvertedMotor(true);
	leftController->Encoder::SetReverseDirection(true);
	rightController->Encoder::SetReverseDirection(true);
}

Chassis::~Chassis()
{
	delete leftController;
	delete rightController;
	delete drive;
	delete gyro;
	delete shifter;
}

void Chassis::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new JoystickTank("Default Tank Drive"));
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
	return encoderUnitsToFeet((leftController->GetDistance()+rightController->GetDistance())/2.0);
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
	if(isUsingEncoders){
		leftController->UseEncoder(smart);
		rightController->UseEncoder(smart);
	} else {
		leftController->UseEncoder(false);
		rightController->UseEncoder(false);
	}
}

void Chassis::ProjectSensors() {
	SmartDashboard::PutNumber("Chassis Gyro Angle", gyro->GetAngle());
	SmartDashboard::PutNumber("Chassis Gyro Rate",  gyro->GetRate());
	SmartDashboard::PutNumber("Chassis Left  Raw",      leftController->Encoder::GetRaw());
	SmartDashboard::PutNumber("Chassis Right Raw",      rightController->Encoder::GetRaw());
	SmartDashboard::PutNumber("Chassis Left  Velocity", leftController->GetRate());
	SmartDashboard::PutNumber("Chassis Right Velocity", rightController->GetRate());
}

/*
 * 1 EncoderUnit is defined as the maximum number of ticks counted by one encoder,
 * for one drive motor, in one second, at maximum robot voltage. 12.0 inches in 1 foot.
*/
double Chassis::encoderUnitsToFeet(double units){
	double conversionFactor = 3.141592654 * N_WHEEL_DIAMETER / 12.0;
	conversionFactor *= ENCODER_TOP_SPEED / N_ENCODER_PPR;
	return units*conversionFactor;
}

/*
 * 1 EncoderUnit is defined as the maximum number of ticks counted by one encoder,
 * for one drive motor, in one second, at maximum robot voltage. 12.0 inches in 1 foot.
*/
double Chassis::feetToEncoderUnits(double feet){
	double conversionFactor = 3.141592654 * N_WHEEL_DIAMETER / 12.0;
	conversionFactor *= ENCODER_TOP_SPEED / N_ENCODER_PPR;
	return feet/conversionFactor;
}

void Chassis::ShiftGear(bool isHigh) {
	shifter->Set(isHigh);
}

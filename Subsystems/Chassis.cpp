/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty, Mikhail Kyraha                                  */
/*-------------------------------------------------------------------------*/
#include "../Robotmap.h"
#include "../Commands/JoystickTank.h"
#include "../Commands/JoystickStraight.h"
#include "../Commands/LogChassis.h"
#include "Chassis.h"
#include "math.h"
#include "string.h"

Chassis::Chassis() : LogSubsystem("Chassis"){
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
	Robot::preferences->GetDouble("EncoderTopSpeed",7200);
}

void Chassis::InitLogCommand() {
	SetLogCommand(new LogChassis());
}

void Chassis::InitEncoders() {
	leftController->SetDistancePerPulse(1.0/Robot::preferences->GetDouble("EncoderTopSpeed",3000));
	rightController->SetDistancePerPulse(1.0/Robot::preferences->GetDouble("EncoderTopSpeed",3000));
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

double Chassis::encoderUnitsToFeet(double units){
	//1 EncoderUnit is defined as the maximum number of ticks counted by one encoder, for one drive motor, in one second, at maximum robot voltage.
	double conversionFactor = 3.141592654 * N_WHEEL_DIAMETER / 12.0;
	conversionFactor *= Robot::preferences->GetDouble("EncoderTopSpeed") / N_ENCODER_PPR;
	return units*conversionFactor;
}

double Chassis::feetToEncoderUnits(double feet){
	// 1 EncoderUnit is defined as the maximum number of ticks counted by one encoder, for one drive motor, in one second, at maximum robot voltage.
	double conversionFactor = 3.141592654 * N_WHEEL_DIAMETER / 12.0;
	conversionFactor *= Robot::preferences->GetDouble("EncoderTopSpeed") / N_ENCODER_PPR;
	return feet/conversionFactor;
}

void Chassis::ShiftGear(bool isHigh) {
	shifter->Set(isHigh);
}

bool Chassis::GetShiftPos() {
	return shifter->Get();
}


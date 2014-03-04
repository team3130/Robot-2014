/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: Ashwin Chetty, Mikhail Kyraha                                  */
/*-------------------------------------------------------------------------*/
#include "../Robotmap.h"
#include "../Commands/JoystickTank.h"
#include "../Commands/JoystickStraight.h"
#include "../CommandBase.h"
#include "../Robot.h"
#include "Logger.h"
#include "Chassis.h"
#include "math.h"
#include "string.h"

Chassis::Chassis() : Subsystem("Chassis"){
	isUsingGyro = false;
	leftController = new VelocityController("Left", C_LEFTMOTOR,C_LEFTSATELLITE,C_ENCODER_LEFT_A,C_ENCODER_LEFT_B);
	rightController = new VelocityController("Right", C_RIGHTMOTOR,C_RIGHTSATELLITE,C_ENCODER_RIGHT_A,C_ENCODER_RIGHT_B);
	shifter = new Solenoid(C_SHIFTER);
	gyro  = new Gyro(C_GYRO);
	drive = new RobotDrive(leftController, rightController);
	// Never use RobotDrive's SetInvertedMotor, use VelocityConltroller's one instead
	drive->SetSafetyEnabled(false);
	leftController->SetInvertedMotor(true);
	rightController->SetInvertedMotor(true);
	leftController->Encoder::SetReverseDirection(true);
	rightController->Encoder::SetReverseDirection(true);
	if(Robot::LeftEncoderPPR>0){
		//leftController->SetDistancePerPulse(M_PI * N_WHEEL_DIAMETER * N_WHEEL_ENCODER_RATIO / Robot::LeftEncoderPPR);
		isLeftEncoderOK = true;
	}
	else isLeftEncoderOK = false;
	if(Robot::RightEncoderPPR>0) {
		//rightController->SetDistancePerPulse(M_PI * N_WHEEL_DIAMETER * N_WHEEL_ENCODER_RATIO / Robot::RightEncoderPPR);
		isRightEncoderOK = true;
	}
	else isRightEncoderOK = false;

	Robot::logger->add_sensor(new Sensor<Gyro>("Chassis.Gyro.Rate", *gyro, Sensor<Gyro>::DOUBLE, (Sensor<Gyro>::d_funcPtr_t)&Gyro::GetRate));
	Robot::logger->add_sensor(new Sensor<Gyro>("Chassis.Gyro.Angle", *gyro, Sensor<Gyro>::FLOAT, &Gyro::GetAngle));
	Robot::logger->add_sensor(new Sensor<Encoder>("Chassis.LeftController.Encoder.Rate", (Encoder&)*leftController, Sensor<Encoder>::DOUBLE, &Encoder::GetRate));
	Robot::logger->add_sensor(new Sensor<Encoder>("Chassis.RightController.Encoder.Rate", (Encoder&)*rightController, Sensor<Encoder>::DOUBLE, &Encoder::GetRate));
	Robot::logger->add_sensor(new Sensor<Encoder>("Chassis.LeftController.Encoder.Distance", (Encoder&)*leftController, Sensor<Encoder>::DOUBLE, &Encoder::GetDistance));
	Robot::logger->add_sensor(new Sensor<Encoder>("Chassis.RightController.Encoder.Distance", (Encoder&)*rightController, Sensor<Encoder>::DOUBLE, &Encoder::GetDistance));
}

/*
Chassis::~Chassis()
{
	delete leftController;
	delete rightController;
	delete drive;
	delete gyro;
	delete shifter;
}
*/

void Chassis::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new JoystickTank("Default Tank Drive"));
}

void Chassis::InitEncoders() {
	leftController->Reset();
	rightController->Reset();
	leftController->Start();
	rightController->Start();
}

double Chassis::GetDistance() {
	double totalDistance = 0;
	int nEncoders = 0;
	if(isLeftEncoderOK) {
		totalDistance += leftController->GetDistance();
		nEncoders++;
	}
	if(isRightEncoderOK) {
		totalDistance += rightController->GetDistance();
		nEncoders++;
	}
	if(nEncoders>0) return totalDistance/nEncoders;
	else return 0;
}

double Chassis::GetRate() {
	double totalRate = 0;
	int nEncoders = 0;
	if(isLeftEncoderOK) {
		totalRate += leftController->GetDistance();
		nEncoders++;
	}
	if(isRightEncoderOK) {
		totalRate += rightController->GetDistance();
		nEncoders++;
	}
	if(nEncoders>0) return totalRate/nEncoders;
	else return 0;
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
	if(CanUseEncoders()){
		leftController->UseEncoder(smart);
		rightController->UseEncoder(smart);
	} else {
		leftController->UseEncoder(false);
		rightController->UseEncoder(false);
	}
}

void Chassis::ProjectSensors() {
	/* Redundant due to logger
	SmartDashboard::PutNumber("Chassis Gyro Angle", gyro->GetAngle());
	SmartDashboard::PutNumber("Chassis Gyro Rate",  gyro->GetRate());
	SmartDashboard::PutNumber("Chassis Left  Raw",      leftController->Encoder::GetRaw());
	SmartDashboard::PutNumber("Chassis Right Raw",      rightController->Encoder::GetRaw());
	SmartDashboard::PutNumber("Chassis Left  Velocity", leftController->GetRate());
	SmartDashboard::PutNumber("Chassis Right Velocity", rightController->GetRate());
	*/
}

/*
 * 1 EncoderUnit is defined as the maximum number of ticks counted by one encoder,
 * for one drive motor, in one second, at maximum robot voltage. 12.0 inches in 1 foot.
double Chassis::encoderUnitsToFeet(double units){
	double conversionFactor = 3.141592654 * N_WHEEL_DIAMETER / 12.0;
	conversionFactor *= ENCODER_TOP_SPEED / N_ENCODER_PPR;
	return units*conversionFactor;
}
*/

void Chassis::ShiftGear(bool isHigh) {
	shifter->Set(isHigh);
}

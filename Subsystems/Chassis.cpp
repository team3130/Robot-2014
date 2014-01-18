#include "../Robotmap.h"
#include "../Commands/JoystickTank.h"
#include "Chassis.h"
#include "math.h"

Chassis::Chassis(int leftMotorChannel, int rightMotorChannel) : Subsystem("Chassis"){
	drive=new RobotDrive(leftMotorChannel, rightMotorChannel);
	drive->SetSafetyEnabled(false);
	precisionMultiplier = 0.6666666666f;
	precisionLevel = 0;
	maxPrecisionLevel = 2;
}
void Chassis::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new JoystickTank());
}
void Chassis::tankDrive(Joystick* left, Joystick* right, int precision){
	precisionLevel = precision;
	float multiplier = pow(precisionMultiplier, precisionLevel);
	float leftStick = left->GetY();
	float rightStick = right->GetY();
	if (fabs(leftStick)<.07){
		leftStick = 0;
	}
	if (fabs(rightStick)<.07){
		rightStick = 0;
	}
	drive->TankDrive(leftStick*multiplier, rightStick*multiplier, false);		//look at the function declaration to see why I put 'false' here.
}
//void Chassis::morePrecision(){
//	precisionLevel++;
//	if(precisionLevel>maxPrecisionLevel)precisionLevel=maxPrecisionLevel;
//}
//void Chassis::lessPrecision(){
//	precisionLevel--;
//	if(precisionLevel<0)precisionLevel=0;
//}
//void Chassis::resetPrecision(){
//	precisionLevel=0;
//}
// Put methods for controlling this subsystem
// here. Call these from Commands.


#include "WPILib.h"

class EncoderRobotDrive : public RobotDrive{
private:
	PIDController* leftPID;
	PIDController* rightPID;
	bool isBypass;
public:
	EncoderRobotDrive(
			SpeedController* leftController, SpeedController* rightController,
			Encoder* leftEncoder, Encoder* rightController);
	virtual ~EncoderRobotDrive();
	void SetLeftRightMotorOutputs(float left, float right);
	void updatePIDValues(double p, double i, double d);
	void DumbRobot();
	void SmartRobot();
};

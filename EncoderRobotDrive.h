#include "WPILib.h"

class EncoderRobotDrive : public RobotDrive{
private:
	PIDController* leftPID;
	PIDController* rightPID;
public:
	EncoderRobotDrive(
			SpeedController* leftController, SpeedController* rightController,
			Encoder* leftEncoder, Encoder* rightController);
	virtual ~EncoderRobotDrive();
	void SetLeftRightMotorOutputs(float left, float right);
	void projectPIDValues();
	void getPIDValues();
	void updatePIDValues();
};

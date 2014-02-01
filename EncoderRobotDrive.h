#include "WPILib.h"
class EncoderRobotDrive : public RobotDrive{
private:
	PIDController leftPID;
	PIDController rightPID;
public:
	EncoderRobotDrive(SpeedController* left, SpeedController* right);
	void SetLeftRightMotorOutputs(float left, float right);
};

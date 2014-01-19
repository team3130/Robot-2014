#ifndef ROTATE_H
#define ROTATE_H

#include "../CommandBase.h"

/**
 * @author Ashwin
 * 
 * The Rotate command uses the gyroscope to rotate the
 * robot by a specific angle. We should calculate angles
 * in degrees.
 */
class Rotate: public CommandBase {
public:
	Rotate();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

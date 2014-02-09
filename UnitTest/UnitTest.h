/*
 * UnitTest.h
 *
 *  Created on: Feb 6, 2014
 *      Author: M.Kyraha
 */
#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include "Commands/Command.h"
/*
 * Description:
 */
class UnitTest {
private:
	Command* utestRotate;
	Command* utestDriveStraight;
	Command* utestNavigateTo;
	Command* utestExtendIntake;
	Command* utestSpinIntake;
	Command* utestWindCatapult;
	Command* utestShootCatapult;
	Command* utestChangeCatapultEnd;
public:
	UnitTest();
	~UnitTest();
};

#endif

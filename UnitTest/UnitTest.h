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
public:
	UnitTest();
	~UnitTest();
};

#endif

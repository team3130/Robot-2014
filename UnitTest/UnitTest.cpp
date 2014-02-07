/*
 * UnitTest.cpp
 *
 *  Created on: Feb 6, 2014
 *      Author: M.Kyraha
 */

#include "UnitTest.h"
#include "UTestRotate.h"
#include "UTestDriveStraight.h"

/*
 * Default constructor
 */
UnitTest::UnitTest()
{
	utestRotate = new UTestRotate();
	utestDriveStraight = new UTestDriveStraight();
}

/*
 * Default destructor
 */
UnitTest::~UnitTest()
{
	delete utestRotate;
	delete utestDriveStraight;
}

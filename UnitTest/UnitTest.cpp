/*
 * UnitTest.cpp
 *
 *  Created on: Feb 6, 2014
 *      Author: M.Kyraha
 */

#include "UnitTest.h"
#include "UTestRotate.h"
#include "UTestDriveStraight.h"
#include "UTestNavigateTo.h"

/*
 * Default constructor
 */
UnitTest::UnitTest()
{
	utestRotate = new UTestRotate();
	utestDriveStraight = new UTestDriveStraight();
	utestNavigateTo = new UTestNavigateTo();
	//new Rotate("Dummy Rotate");
	//new DriveStraight();
}

/*
 * Default destructor
 */
UnitTest::~UnitTest()
{
	delete utestRotate;
	delete utestDriveStraight;
	delete utestNavigateTo;
}

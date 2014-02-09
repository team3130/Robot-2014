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
#include "UTestExtendIntake.h"
#include "UTestSpinIntake.h"
#include "UTestWindCatapult.h"
#include "UTestShootCatapult.h"
#include "UTestChangeCatapultEnd.h"

/*
 * Default constructor
 */
UnitTest::UnitTest()
{
	utestRotate = new UTestRotate();
	utestDriveStraight = new UTestDriveStraight();
	utestNavigateTo = new UTestNavigateTo();
	utestExtendIntake = new UTestExtendIntake();
	utestSpinIntake = new UTestSpinIntake();
	utestWindCatapult = new UTestWindCatapult();
	utestShootCatapult = new UTestShootCatapult();
	utestChangeCatapultEnd = new UTestChangeCatapultEnd();
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
	delete utestExtendIntake;
	delete utestSpinIntake;
	delete utestWindCatapult;
	delete utestShootCatapult;
	delete utestChangeCatapultEnd;
}

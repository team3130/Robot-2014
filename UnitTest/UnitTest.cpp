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
#include "UTestSpinintake.h"
#include "UTestMoveCatapult.h"
#include "UTestShootCatapult.h"

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
	utestMoveCatapult = new UTestMoveCatapult();
	utestShootCatapult = new UTestShootCatapult();
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
	delete utestMoveCatapult;
	delete utestShootCatapult;
}

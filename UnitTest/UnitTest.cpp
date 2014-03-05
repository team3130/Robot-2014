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
#include "UTestInputs.h"
#include "UTestHotGoal.h"

/*
 * Default constructor
 */
UnitTest::UnitTest()
{
	m_tests.push_back(new UTestRotate());
	m_tests.push_back(new UTestDriveStraight());
	m_tests.push_back(new UTestNavigateTo());
	m_tests.push_back(new UTestInputs());
	m_tests.push_back(new UTestHotGoal());
}

/*
 * Default destructor
 */
UnitTest::~UnitTest()
{
}

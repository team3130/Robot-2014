/*
 * UnitTest.h
 *
 *  Created on: Feb 6, 2014
 *      Author: M.Kyraha
 */
#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <vector>
#include "Commands/Command.h"
/*
 * Description:
 */
class UnitTest {
private:
	std::vector<Command*> m_tests;
public:
	UnitTest();
	~UnitTest();
};

#endif

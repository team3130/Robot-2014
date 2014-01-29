/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: <INSERT AUTHOR(S) OF CODE>                                     */
/*-------------------------------------------------------------------------*/

//INCOMPLETE

#include "WPILib.h"
#include "queue"
class SendValue{
public:
	SendValue(int t, std::string k);
	static const int STRING=1;
	static const int BOOLEAN=2;
	static const int NUMBER=3;
	static const int VALUE_TYPE_SPEC=4;
	static const int VALUE=5;
	int type;
	std::string key;
	std::string vs;
	double vd;
	bool vb;
};
class DelayedNetworkTableWrapper{
public:
	NetworkTable* table;
	Timer timer;
	double delay;	//delay in ms.
	DelayedNetworkTableWrapper(std::string table, long msDelay);
	DelayedNetworkTableWrapper(std::string table);
	void PutString(std::string key, std::string value);
	void PutNumber(std::string key, double value);
	void PutBoolean(std::string key, bool value);
};

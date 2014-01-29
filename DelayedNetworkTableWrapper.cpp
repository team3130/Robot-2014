/*-------------------------------------------------------------------------*/
/* Copyright (c) 2014 FRC-3130 "ERROR 3130". All Rights Reserved.          */
/* Open Source Software - may be modified, shared, used and reused by FRC  */
/* teams under the same license as the WPILib code itself.                 */
/* Authors: <INSERT AUTHOR(S) OF CODE>                                     */
/*-------------------------------------------------------------------------*/

//INCOMPLETE

#include "WPILib.h"
#include "DelayedNetworkTableWrapper.h"

SendValue::SendValue(int t, std::string k){
	key=k;
}

DelayedNetworkTableWrapper::DelayedNetworkTableWrapper(std::string name, long msDelay){
	table=NetworkTable::GetTable(name);
	delay=msDelay>10?msDelay:10;	//absolute minimum is 10ms.
}
DelayedNetworkTableWrapper::DelayedNetworkTableWrapper(std::string name){
	table=NetworkTable::GetTable(name);
	delay=10;
}
void DelayedNetworkTableWrapper::PutString(std::string key, std::string value){
	table->PutString(key,value);
}
void DelayedNetworkTableWrapper::PutNumber(std::string key, double value){
	table->PutNumber(key,value);
}
void DelayedNetworkTableWrapper::PutBoolean(std::string key, bool value){
	table->PutBoolean(key,value);
}

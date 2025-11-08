/*
 * Com.cpp
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 */

#include "Com.h"

Com::Com() {
	// TODO Auto-generated constructor stub

}


Com::~Com() {
	// TODO Auto-generated destructor stub
}


//Com::Com(const Com &other) {}
//Com::Com(Com &&other) {}
//Com& Com::operator=(const Com &other) {}
//Com& Com::operator=(Com &&other) {}


Com::ErrorCode sendCmd(std::string cmd)
{
	return Com::ErrorCode::OK;
}


std::string getResponse()
{
	return "test";
}


//TODO: return OK or NOT_OK
Com::ErrorCode init()
{
	return Com::ErrorCode::OK;
}


Com::ErrorCode deinit()
{
	return Com::ErrorCode::OK;
}


//TODO: return OK or NOT_OK
Com::ErrorCode resetHW()
{
	return Com::ErrorCode::OK;
}


//TODO: return OK or NOT_OK
Com::ErrorCode resetSW()
{
	return Com::ErrorCode::OK;
}





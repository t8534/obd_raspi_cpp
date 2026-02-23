/*
 * Com.cpp
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 */

#include "Com.h"

Com::Com() {}


Com::~Com() {}


//Com::Com(const Com &other) {}
//Com::Com(Com &&other) {}
//Com& Com::operator=(const Com &other) {}
//Com& Com::operator=(Com &&other) {}


Com::ErrorCode Com::sendCmd(std::string cmd)
{
	return Com::ErrorCode::OK;
}


std::string Com::getResponse()
{
	return "test";
}


//TODO: return OK or NOT_OK
Com::ErrorCode Com::init()
{
	return Com::ErrorCode::OK;
}


Com::ErrorCode Com::deinit()
{
	return Com::ErrorCode::OK;
}


//TODO: return OK or NOT_OK
Com::ErrorCode Com::resetHW()
{
	return Com::ErrorCode::OK;
}


//TODO: return OK or NOT_OK
Com::ErrorCode Com::resetSW()
{
	return Com::ErrorCode::OK;
}





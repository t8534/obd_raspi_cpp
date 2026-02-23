/*
 * ComSimu.cpp
 *
 *  Created on: 23 lut 2026
 *      Author: arek1
 */

#include "ComSimu.h"

ComSimu::ComSimu() {}

ComSimu::~ComSimu() {}


//ComSimu::ComSimu(const ComSimu &other) {}
//ComSimu::ComSimu(ComSimu &&other) {}
//ComSimu& ComSimu::operator=(const ComSimu &other) {}
//ComSimu& ComSimu::operator=(ComSimu &&other) {}

ComSimu::ErrorCode ComSimu::sendCmd(std::string cmd)
{
	return ComSimu::ErrorCode::OK;
}


std::string ComSimu::getResponse()
{
	return "test";
}


//TODO: return OK or NOT_OK
ComSimu::ErrorCode ComSimu::init()
{
	return ComSimu::ErrorCode::OK;
}


ComSimu::ErrorCode ComSimu::deinit()
{
	return ComSimu::ErrorCode::OK;
}


//TODO: return OK or NOT_OK
ComSimu::ErrorCode ComSimu::resetHW()
{
	return ComSimu::ErrorCode::OK;
}


//TODO: return OK or NOT_OK
ComSimu::ErrorCode ComSimu::resetSW()
{
	return ComSimu::ErrorCode::OK;
}


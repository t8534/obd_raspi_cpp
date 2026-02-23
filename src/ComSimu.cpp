/*
 * ComSimu.cpp
 *
 *  Created on: 23 lut 2026
 *      Author: arek1
 */

#include "ComSimu.h"

ComSimu::ComSimu() { responseBuffer = "";}

ComSimu::~ComSimu() {}


//ComSimu::ComSimu(const ComSimu &other) {}
//ComSimu::ComSimu(ComSimu &&other) {}
//ComSimu& ComSimu::operator=(const ComSimu &other) {}
//ComSimu& ComSimu::operator=(ComSimu &&other) {}


ComSimu::Command ComSimu::parseCommand(const std::string& s)
{
    if (s == "START") return Command::Start;
    if (s == "STOP")  return Command::Stop;
    if (s == "PAUSE") return Command::Pause;

    return Command::Unknown;
}

ComSimu::ErrorCode ComSimu::sendCmd(std::string cmdString)
{
	ErrorCode res = NOT_OK;

	Command cmd = parseCommand(cmdString);

	switch (cmd) {
	    case Command::Start:
	    	responseBuffer = "This is response to Start command";
	        break;

	    case Command::Stop:
	    	responseBuffer = "This is response to Stop command";
	        break;

	    case Command::Pause:
	    	responseBuffer = "This is response to Pause command";
	        break;

	    default:
	    	responseBuffer = "This is response - Unknown command";

	}

	return res;
}


std::string ComSimu::getResponse()
{
	return responseBuffer;
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





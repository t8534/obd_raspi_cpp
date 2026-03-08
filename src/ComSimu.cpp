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


//ComSimu::Command ComSimu::parseCommand(const std::string& s)
ComSimu::Command ComSimu::parseCommand(const char* s)
{
	std::string cmdString(s);

    if (cmdString == "Mode01Cmd") return Command::Mode01Cmd;
    if (cmdString == "Mode01PID05Cmd")  return Command::Mode01PID05Cmd;
    if (cmdString == "Mode01PID11Cmd") return Command::Mode01PID11Cmd;
    if (cmdString == "Mode01PID12Cmd") return Command::Mode01PID12Cmd;
    if (cmdString == "Mode03Cmd") return Command::Mode03Cmd;

    return Command::UnkownCmc;
}

//ComSimu::ErrorCode ComSimu::sendCmd(std::string cmdString)
ComSimu::ErrorCode ComSimu::sendCmd(const char* cmdString) const
{
	ErrorCode res = NOT_OK;
/*
	Command cmd = parseCommand(cmdString);

	switch (cmd) {
	    case Command::Mode01Cmd:
	    	responseBuffer = "This is response to Mode01Cmd command";
	        break;

	    case Command::Mode01PID05Cmd:
	    	responseBuffer = "This is response to Mode01PID05Cmd command";
	        break;

	    case Command::Mode01PID11Cmd:
	    	responseBuffer = "This is response to Mode01PID11Cmd command";
	        break;

	    case Command::Mode01PID12Cmd:
	    	responseBuffer = "This is response to Mode01PID12Cmd command";
	        break;

	    case Command::Mode03Cmd:
	    	responseBuffer = "This is response to Mode03Cmd command";
	        break;

	    default:
	    	responseBuffer = "This is response - Unknown command";

	}
*/
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





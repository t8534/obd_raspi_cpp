/*
 * ParserMode01PID05.h
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 */

#ifndef PARSERMODE01PID05_H_
#define PARSERMODE01PID05_H_

#include "OBDParserModePID.h"

class ParserMode01PID05 : public OBDParserModePID
{
public:
	ParserMode01PID05();
	virtual ~ParserMode01PID05();

	//ParserMode01PID05(const ParserMode01PID05 &other);
	//ParserMode01PID05(ParserMode01PID05 &&other);
	//ParserMode01PID05& operator=(const ParserMode01PID05 &other);
	//ParserMode01PID05& operator=(ParserMode01PID05 &&other);

	//TODO: is virtual necessary as we were never here a base class for others ?
    virtual std::string getCmdLine() {return CMD_LINE; };

    //TODO: is virtual necessary as we were never here a base class for others ?
    virtual RetStatus processData(std::string& data);

    //TODO: is virtual necessary as we were never here a base class for others ?
    virtual std::string toString() {return "I am " + pidName; };

private:
    std::string pidName;
    static constexpr const char* CMD_LINE = "This is a command line from ParserModePID05";

};

#endif /* PARSERMODE01PID05_H_ */


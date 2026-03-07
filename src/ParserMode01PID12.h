/*
 * ParserMode01PID12.h
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 */

#ifndef PARSERMODE01PID12_H_
#define PARSERMODE01PID12_H_

#include "OBDParserModePID.h"

class ParserMode01PID12 : public OBDParserModePID
{
public:
	ParserMode01PID12();
	virtual ~ParserMode01PID12();

	//ParserMode01PID12(const ParserMode01PID12 &other);
	//ParserMode01PID12(ParserMode01PID12 &&other);
	//ParserMode01PID12& operator=(const ParserMode01PID12 &other);
	//ParserMode01PID12& operator=(ParserMode01PID12 &&other);

	//TODO: is virtual necessary as we were never here a base class for others ?
    virtual std::string getCmdLine() {return CMD_LINE; };

    //TODO: is virtual necessary as we were never here a base class for others ?
    virtual RetStatus processData(std::string& data);

    //TODO: is virtual necessary as we were never here a base class for others ?
    virtual std::string toString() {return "I am " + pidName; };

private:
    std::string pidName;
    static constexpr const char* CMD_LINE = "This is a command line from ParserModePID12";

};

#endif /* PARSERMODE01PID12_H_ */



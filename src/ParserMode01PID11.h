/*
 * ParserMode01PID11.h
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 */

#ifndef PARSERMODE01PID11_H_
#define PARSERMODE01PID11_H_

#include "OBDParserModePID.h"

class ParserMode01PID11 : public OBDParserModePID
{
public:
	ParserMode01PID11();
	virtual ~ParserMode01PID11();


	//ParserMode01PID11(const ParserMode01PID11 &other);
	//ParserMode01PID11(ParserMode01PID11 &&other);
	//ParserMode01PID11& operator=(const ParserMode01PID11 &other);
	//ParserMode01PID11& operator=(ParserMode01PID11 &&other);

	//TODO: is virtual necessary as we were never here a base class for others ?
    virtual std::string getCmdLine() {return CMD_LINE; };

    //TODO: is virtual necessary as we were never here a base class for others ?
    virtual RetStatus processData(std::string& data);

    //TODO: is virtual necessary as we were never here a base class for others ?
    virtual std::string toString() {return "I am " + pidName; };

private:
    std::string pidName;
    static constexpr const char* CMD_LINE = "This is a command line from ParserModePID11";

};

#endif /* PARSERMODE01PID11_H_ */


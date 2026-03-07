/*
 * ParserMode03.h
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 * 
 * 
 */

#ifndef PARSERMODE03_H_
#define PARSERMODE03_H_

#include "OBDParserMode.h"

class ParserMode03 : public OBDParserMode
{
public:
	ParserMode03();
	virtual ~ParserMode03();

	//ParserMode03(const ParserMode01 &other);
	//ParserMode03(ParserMode01 &&other);
	//ParserMode03& operator=(const ParserMode01 &other);
	//ParserMode03& operator=(ParserMode01 &&other);

	virtual std::string getCmdLine() {return CMD_LINE; };

	std::string toString() {return "I am " + modeName; };

private:
    std::string modeName;
    static constexpr const char* CMD_LINE = "This is a command line from OBDParserMode03";

};

#endif /* PARSERMODE03_H_ */

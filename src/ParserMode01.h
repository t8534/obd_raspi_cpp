/*
 * ParserMode01.h
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 * 
 * 
 */

#ifndef PARSERMODE01_H_
#define PARSERMODE01_H_

#include "OBDParserMode.h"

class ParserMode01 : public OBDParserMode
{
public:
	ParserMode01();
	virtual ~ParserMode01();

	//ParserMode01(const ParserMode01 &other);
	//ParserMode01(ParserMode01 &&other);
	//ParserMode01& operator=(const ParserMode01 &other);
	//ParserMode01& operator=(ParserMode01 &&other);

	//virtual std::string getCmdLine() {return CMD_LINE; };
	virtual const char* getCmdLine() {return REQUEST; };


	std::string toString() {return modeName; };

private:
    std::string modeName;

    // For each Mode that has PIDs, there should be no Request (Command Line) itself.
    // So command line should be empty, this is detected than by CmdManager cycle loop.
    // For for Modes that have no PIDs, like Mode03, the Request is defined.
    //static constexpr const char* REQUEST = "REQUEST Mode01";
    static constexpr const char* REQUEST = "";

};

#endif /* PARSERMODE01_H_ */

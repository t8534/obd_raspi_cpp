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

	std::string toString();

};

#endif /* PARSERMODE01PID11_H_ */


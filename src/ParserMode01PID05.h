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


	std::string toString();

};

#endif /* PARSERMODE01PID05_H_ */


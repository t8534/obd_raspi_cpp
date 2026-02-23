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

	std::string toString();

};

#endif /* PARSERMODE01PID12_H_ */



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

	std::string toString();

};

#endif /* PARSERMODE01_H_ */

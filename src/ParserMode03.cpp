/*
 * ParserMode03.cpp
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 * 
 * Description:
 * SAE J1979 Test Mode 03 - show diagnostic trouble codes
 * 
 * https://en.wikipedia.org/wiki/OBD-II_PIDs
 * 
 * PID: N/A
 * Data bytes returned: n * 6
 * Description: Request trouble codes 
 * Min value: N/A
 * Max value: N/A
 * Units: N/A
 * Formula: 3 codes per message frame, see details at wiki above.
 *
 * 
 */

#include "ParserMode03.h"

ParserMode03::ParserMode03() {
	// TODO Auto-generated constructor stub

}

ParserMode03::~ParserMode03() {
	// TODO Auto-generated destructor stub
}


//ParserMode03::ParserMode03(const ParserMode03 &other) {}
//ParserMode03::ParserMode03(ParserMode03 &&other) {}
//ParserMode03& ParserMode03::operator=(const ParserMode03 &other) {}
//ParserMode03& ParserMode03::operator=(ParserMode03 &&other) {}

std::string ParserMode03::toString()
{
	std::string ret = "I am ParserMode03";

	return ret;
}




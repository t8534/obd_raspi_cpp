/*
 * ParserMode01PID05.cpp
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 * 
 * Description:
 * https://en.wikipedia.org/wiki/OBD-II_PIDs
 * 
 * SAE J1979 Test Mode 01 - show current data
 * PID (dec) 05
 * Data bytes returned: 1
 * Description: Engine coolant temperature
 * Min value: -40
 * Max value: 215
 * Units: C
 * Formula: A - 40
 * 
 * 
 */

#include "ParserMode01PID05.h"

ParserMode01PID05::ParserMode01PID05() {
	// TODO Auto-generated constructor stub

}

ParserMode01PID05::~ParserMode01PID05() {
	// TODO Auto-generated destructor stub
}


//ParserMode01PID05::ParserMode01PID05(const ParserMode01PID05 &other) {}
//ParserMode01PID05::ParserMode01PID05(ParserMode01PID05 &&other) {}
//ParserMode01PID05& ParserMode01PID05::operator=(const ParserMode01PID05 &other) {}
//ParserMode01PID05& ParserMode01PID05::operator=(ParserMode01PID05 &&other) {}

std::string ParserMode01PID05::toString()
{
	std::string ret = "I am ParserMode01PID05";

	return ret;
}




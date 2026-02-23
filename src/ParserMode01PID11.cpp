/*
 * ParserMode01PID11.cpp
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 * 
 * Description:
 * https://en.wikipedia.org/wiki/OBD-II_PIDs
 * 
 * SAE J1979 Test Mode 01 - show current data
 * PID (dec) 11
 * Data bytes returned: 1
 * Description: Intake manifold absolute pressure 
 * Min value: 0
 * Max value: 255
 * Units: kPa
 * Formula: A
 * 
 * 
 */

#include "ParserMode01PID11.h"

ParserMode01PID11::ParserMode01PID11() {
	// TODO Auto-generated constructor stub

}

ParserMode01PID11::~ParserMode01PID11() {
	// TODO Auto-generated destructor stub
}


//ParserMode01PID11::ParserMode01PID11(const ParserMode01PID11 &other) {}
//ParserMode01PID11::ParserMode01PID11(ParserMode01PID11 &&other) {}
//ParserMode01PID11& ParserMode01PID11::operator=(const ParserMode01PID11 &other) {}
//ParserMode01PID11& ParserMode01PID11::operator=(ParserMode01PID11 &&other) {}

std::string ParserMode01PID11::toString()
{
	std::string ret = "I am ParserMode01PID11";

	return ret;
}




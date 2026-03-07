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

ParserMode01PID05::ParserMode01PID05()
{
    pidName = "ParserModePID05";
}

ParserMode01PID05::~ParserMode01PID05() {}


//ParserMode01PID05::ParserMode01PID05(const ParserMode01PID05 &other) {}
//ParserMode01PID05::ParserMode01PID05(ParserMode01PID05 &&other) {}
//ParserMode01PID05& ParserMode01PID05::operator=(const ParserMode01PID05 &other) {}
//ParserMode01PID05& ParserMode01PID05::operator=(ParserMode01PID05 &&other) {}

OBDParserModePID::RetStatus ParserMode01PID05::processData(std::string& data)
{
	RetStatus ret = RetStatus::NOT_OK;

	/*
    for (const auto& n : modePIDs)
    {
        if (n)  // TODO: is it really necessary ?
            std::cout << n->toString() << std::endl;
    }
    */

    ret = RetStatus::OK;

	return ret;
}





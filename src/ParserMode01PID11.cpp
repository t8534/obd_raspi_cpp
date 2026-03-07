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
    pidName = "ParserModePID11";
}

ParserMode01PID11::~ParserMode01PID11() {}

//ParserMode01PID11::ParserMode01PID11(const ParserMode01PID11 &other) {}
//ParserMode01PID11::ParserMode01PID11(ParserMode01PID11 &&other) {}
//ParserMode01PID11& ParserMode01PID11::operator=(const ParserMode01PID11 &other) {}
//ParserMode01PID11& ParserMode01PID11::operator=(ParserMode01PID11 &&other) {}

OBDParserModePID::RetStatus ParserMode01PID11::processData(std::string& data)
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



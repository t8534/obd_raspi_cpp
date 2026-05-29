/*
 * ParserMode01PID12.cpp
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 * 
 * Description:
 * https://en.wikipedia.org/wiki/OBD-II_PIDs
 * 
 * SAE J1979 Test Mode 01 - show current data
 * PID (dec) 12 (0x0C)
 * Data bytes returned: 2
 * Description: Engine speed
 * Min value: 0
 * Max value: 16383.75
 * Units: rpm
 * Formula: ((256 * A) + B) / 4
 * 
 * Notes
 * 
 * The references A, B, C, D in the formula table are byte positions in the returned data. 
 * Note for instance that engine load return as single byte and so only A is used in the formula,
 * whereas engine speed returns 2 bytes and so A and B are used in the formula to calculate speed.
 *
 * The first byte to be returned is A, followed by B, C, and D. When referring to bits in each byte,
 * quantities like C4 means bit 4 from data byte C. Each bit is numbered from 0 to 7, with 7 being
 * the most significant bit and 0 is the least significant bit.
 *
 * A                        B                        C                        D 
 * A7 A6 A5 A4 A3 A2 A1 A0  B7 B6 B5 B4 B3 B2 B1 B0  C7 C6 C5 C4 C3 C2 C1 C0  D7 D6 D5 D4 D3 D2 D1 D0
 *
 * !!!
 * In E:\projects\obd_raspi\docs\obd.pdf it look like C and D are always 0x00:
 *
 * Request: 01C1
 * Response: 41 0C 1A 4E 00 00
 * Formula: ((256 * A) + B) / 4
 * 
 * Both formulas are different than one presented in ELM pdf, that is just:
 *     Response: 41 0C 1A F8
 *     1A F8 -> 6904 dec
 *     Formula: 6904 (dec) / 4 = 1726 rpm
 *
 *
 * 
 */

#include "ParserMode01PID12.h"

ParserMode01PID12::ParserMode01PID12()
{
    pidName = "ParserMode01PID12";
}

ParserMode01PID12::~ParserMode01PID12() {}

//ParserMode01PID12::ParserMode01PID12(const ParserMode01PID12 &other) {}
//ParserMode01PID12::ParserMode01PID12(ParserMode01PID12 &&other) {}
//ParserMode01PID12& ParserMode01PID12::operator=(const ParserMode01PID12 &other) {}
//ParserMode01PID12& ParserMode01PID12::operator=(ParserMode01PID12 &&other) {}

OBDParserModePID::RetStatus ParserMode01PID12::processData(std::string& data)
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





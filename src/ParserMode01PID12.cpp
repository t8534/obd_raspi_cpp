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
 * PID (dec) 12
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
 * 
 * 
 */

#include "ParserMode01PID12.h"

ParserMode01PID12::ParserMode01PID12() {
	// TODO Auto-generated constructor stub

}

ParserMode01PID12::~ParserMode01PID12() {
	// TODO Auto-generated destructor stub
}


//ParserMode01PID12::ParserMode01PID12(const ParserMode01PID12 &other) {}
//ParserMode01PID12::ParserMode01PID12(ParserMode01PID12 &&other) {}
//ParserMode01PID12& ParserMode01PID12::operator=(const ParserMode01PID12 &other) {}
//ParserMode01PID12& ParserMode01PID12::operator=(ParserMode01PID12 &&other) {}

std::string ParserMode01PID12::toString()
{
	std::string ret = "I am ParserMode01PID12";

	return ret;
}





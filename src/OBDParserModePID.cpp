/*
 * OBDParserModePID.cpp
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 */



#include "OBDParserModePID.h"

OBDParserModePID::OBDParserModePID() {
	// TODO Auto-generated constructor stub

}

OBDParserModePID::~OBDParserModePID() {
	// TODO Auto-generated destructor stub
}


//OBDParserModePID::OBDParserModePID(const OBDParserModePID &other) {}
//OBDParserModePID::OBDParserModePID(OBDParserModePID &&other) {}
//OBDParserModePID& OBDParserModePID::operator=(const OBDParserModePID &other) {}
//OBDParserModePID& OBDParserModePID::operator=(OBDParserModePID &&other) {}


OBDParserModePID::ErrorCode configure(bool pidSelected)
{
	OBDParserModePID::ErrorCode ret = OBDParserModePID::ErrorCode::NOT_OK;

	selected = pidSelected;

	return ret;
}


OBDParserModePID::ErrorCode parseData(std::string data)
{
	OBDParserModePID::ErrorCode ret = OBDParserModePID::ErrorCode::NOT_OK;



	return ret;
}


std::string toString()
{
	std::string ret = "";

	return ret;
}

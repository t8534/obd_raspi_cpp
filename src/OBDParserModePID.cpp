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


OBDParserModePID::RetStatus OBDParserModePID::configure(bool pidSelected)
{
	RetStatus ret = RetStatus::NOT_OK;

	selected = pidSelected;

	return ret;
}


std::string OBDParserModePID::getCmdLine()
{
	std::string ret = "";

	return ret;
}


OBDParserModePID::RetStatus OBDParserModePID::parseData(std::string data)
{
	RetStatus ret = RetStatus::NOT_OK;

	return ret;
}


OBDParserModePID::RetStatus OBDParserModePID::processingData(std::string data)
{
	RetStatus ret = RetStatus::NOT_OK;

	return ret;
}


std::string OBDParserModePID::toString()
{
	std::string ret = "";

	return ret;
}

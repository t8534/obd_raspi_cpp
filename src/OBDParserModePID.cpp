/*
 * OBDParserModePID.cpp
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 */



#include "OBDParserModePID.h"

OBDParserModePID::OBDParserModePID()
{
    pidName = "OBDParserModePID - base class";
}

OBDParserModePID::~OBDParserModePID() {}


//OBDParserModePID::OBDParserModePID(const OBDParserModePID &other) {}
//OBDParserModePID::OBDParserModePID(OBDParserModePID &&other) {}
//OBDParserModePID& OBDParserModePID::operator=(const OBDParserModePID &other) {}
//OBDParserModePID& OBDParserModePID::operator=(OBDParserModePID &&other) {}


//TODO: is this still necessary for PID ?
OBDParserModePID::RetStatus OBDParserModePID::configure(bool pidSelected)
{
	RetStatus ret = RetStatus::NOT_OK;

	return ret;
}


OBDParserModePID::RetStatus OBDParserModePID::processData(std::string& data)
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



/*
 * OBDParserMode.cpp
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 */

#include "OBDParserMode.h"

OBDParserMode::OBDParserMode() {
	// TODO Auto-generated constructor stub

}

OBDParserMode::~OBDParserMode() {
	// TODO Auto-generated destructor stub
}


//OBDParserMode::OBDParserMode(const OBDParserMode &other) {}
//OBDParserMode::OBDParserMode(OBDParserMode &&other) {}
//OBDParserMode& OBDParserMode::operator=(const OBDParserMode &other) {}
//OBDParserMode& OBDParserMode::operator=(OBDParserMode &&other) {}


//TODO: Called during app initialization from Config.
// It should set selected or not this module.
// And if selected it should load selected PIDs nad select each od them by calling
// their configure() function
//
// TODO:
// Should as a parameter be list of PIDs objects for processing, or just their names
// or indexes. But it looks like the list of objects, created in Config on the base
// of expected configuration.
// !! However who is responsible for clear this list ? Probably Config, because
// if selected modes and PIDs will be changes, the Config starting its work from
// the beginning.
//
// TODO: perhaps PIDsList should be copied as a move semantic here

// Parameters:
// modeSelected - true or false. Is this OBD mode selected for processing or not
// PIDsList - the list of OBDParserModePID objects selected for processing
//
OBDParserMode::ErrorCode configure(bool modeSelected, std::vector &PIDsList)
{
	OBDParserMode::ErrorCode ret = OBDParserMode::ErrorCode::NOT_OK;

    if (modeSelected == true)
    {
        for (int n : PIDsList)
        {
            n.config(true);    //TODO: possible we need iterator here, in place of for above
    	    modePIDs.push_back(OBDParserModePID);
        }
    }

    // Iterator example
    //for (auto it = PIDsList.begin(); it != PIDsList.end(); ++it)
    //    std::cout << *it << " ";


    ret = OBDParserMode::ErrorCode::OK;

	return ret;
}


OBDParserMode::ErrorCode parseData(std::string data)
{
	OBDParserMode::ErrorCode ret = OBDParserMode::ErrorCode::NOT_OK;

	//test
    for (int n : modePIDs)
    {
        std::cout << n.toString() << std::endl;
    }

    ret = OBDParserMode::ErrorCode::OK;

	return ret;
}


std::string toString()
{
	std::string ret = "";

	return ret;
}




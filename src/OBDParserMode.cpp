/*
 * OBDParserMode.cpp
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 * 
 * Description:
 * This is a base class for OBD Mode parsers
 * 
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
// [251230]
// New concept
// The better solution is to create in Configure, the vector with all OBDParseModes and
// linked to them OBDParseModePIDs accordingly.
// The Configure create it on the base of any xml file, or seetings from GUI.
// The Configure create all the content of the vector, so created all the OBD Mode parsers
// and OBD Mode PIDs parsers, following expected configuration.
// The vector contains unique_pointer to created elements.
// All OBD Mode parsers are located in this main vector.
// Unique_pointer to this vector is provided to CmdManager class as a reference &.
// We do not need to && because we do not want to take an ownership. Just we are going
// processing data located in the vector.

// TODO: Change && to &
// We do not want to take the ownership, because we are going to operate on the vector declared in Config class.
OBDParserMode::RetStatus OBDParserMode::configure(std::vector<std::unique_ptr<OBDParserModePID>> &&PIDsList)
{
	RetStatus ret = RetStatus::NOT_OK;

    modePIDs = std::move(PIDsList);  //TODO: This is not necessary because we are

    /*
    if (modeSelected == true)
    {
        for (OBDParserModePID n : PIDsList)
        {
            n.configure(true);    //TODO: possible we need iterator here, in place of for above
    	    modePIDs.push_back(n);
        }
    }
    */

    // Iterator example
    //for (auto it = PIDsList.begin(); it != PIDsList.end(); ++it)
    //    std::cout << *it << " ";


    ret = RetStatus::OK;

	return ret;
}


OBDParserMode::RetStatus OBDParserMode::parseData(std::string data)
{
	RetStatus ret = RetStatus::NOT_OK;

	//test
    for (OBDParserModePID n : modePIDs)
    {
        std::cout << n.toString() << std::endl;
    }

    ret = RetStatus::OK;

	return ret;
}


std::string OBDParserMode::getCmdLine()
{
	std::string ret = "";

	return ret;
}



OBDParserMode::RetStatus processingData(std::string& data)
{
	RetStatus ret = RetStatus::NOT_OK;

	//test
	/*
    for (OBDParserModePID n : modePIDs)
    {
        std::cout << n.toString() << std::endl;
    }
    */

    ret = RetStatus::OK;

	return ret;
}




std::string OBDParserMode::toString()
{
	std::string ret = "I am OBDParserMode";

	return ret;
}




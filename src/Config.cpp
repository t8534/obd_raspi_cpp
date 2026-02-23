/*
 * Config.cpp
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 * 
 * Description:
 * 
 * The Configure manage the vector with all OBDParseModes and linked selected OBDParseModePIDs. 
 * The Configure create it on the base of any xml file, or seetings from GUI.
 * The Configure create all the content of the vector, so create all the OBD Mode parsers
 * and OBD Mode PIDs parsers, following expected configuration.
 * The vector contains unique_pointer to created elements.
 * All OBD Mode parsers are located in this main vector.
 * Unique_pointer to this vector is provided to CmdManager class.
 *
 * 
 */

// TODO:
// [251230]
// Fill up vector list
//
// [260211]
// Implement Constructor only with the operations necessary to initialize object itself.
// Zeroing data, etc. The real configuration processing should be made in configure().
// Think about exceptions throw.


#include "Config.h"
#include "OBDParserMode.h"
#include "ParserMode01.h"
#include "ParserMode03.h"

#include "OBDParserModePID.h"
#include "ParserMode01PID05.h"
#include "ParserMode01PID11.h"
#include "ParserMode01PID12.h"


Config::Config() {
	// TODO Auto-generated constructor stub

}


Config::~Config() {
	// TODO Auto-generated destructor stub
}


//Config::Config(const Config &other) {}
//Config::Config(Config &&other) {}
//Config& Config::operator=(const Config &other) {}
//Config& Config::operator=(Config &&other) {}

//
Config::RetStatus Config::configure()
{
	RetStatus ret = RetStatus::NOT_OK;

    // Fill up vector list - example - USE REAL class not a base class !
	//     std::unique_ptr<OBDParserMode> ptr = std::make_unique<OBDParserMode>();  // This is for C++ 14
    //     std::unique_ptr<OBDParserMode> ptr (new OBDParserMode)    // This is for C++11
	// TODO: here add OBDParserModePID, also use real class not a base one.
	// obdModesList.push_back(ptr);

    // Add ParserMode01 and PIDs 05, 11, 12 dec.
    std::unique_ptr<OBDParserMode> ptr (new ParserMode01);
    std::vector<std::unique_ptr<OBDParserModePID>> pidList;
    pidList.emplace_back(std::unique_ptr<OBDParserModePID>(new ParserMode01PID05));
    pidList.emplace_back(std::unique_ptr<OBDParserModePID>(new ParserMode01PID11));
    pidList.emplace_back(std::unique_ptr<OBDParserModePID>(new ParserMode01PID12));
    ptr->configure(std::move(pidList));   //TODO: do we really need move() here ? Because we have move() inside of ptr->configure
    pidList.clear();
    obdModesList.emplace_back(std::move(ptr));
    ptr.reset();
    
    // Add ParserMode03
    std::unique_ptr<OBDParserMode> ptr (new ParserMode03);
    obdModesList.emplace_back(std::move(ptr));


/*	
    if (modeSelected == true)
    {
        for (OBDParserModePID n : PIDsList)
        {
            n.config(true);    //TODO: possible we need iterator here, in place of for above
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


// External code could only read it but not modify.
// The usage is:
// Config cfg;
// for (const auto& title : cfg.getOBDModeList()) {
//     std::cout << title << std::endl;
// }
//
// Key points:
// Returns a const reference — efficient, no copy.
// Callers cannot modify the list (compiler prevents it).
// Use this form almost always if you only need to expose data for reading.
const std::vector<std::unique_ptr<OBDParserMode>>& Config::getOBDModesList() const
{
    return obdModesList;
}


// Read-write access (controlled modification)
//
// Gives full control (can modify, add, or remove elements).
// Fast — no copying.
// Be careful: this breaks encapsulation if you expose internals freely.
// Good for low-level containers, not recommended for complex domain models.
//
// If you want to allow external code to modify the vector directly:
// 
// std::vector<std::unique_ptr<OBDParserMode>>& Config::getOBDModeList()
// {
//     return obdModesList;
// }
//
// Optionally, also keep the const version:
//
// const std::vector<std::unique_ptr<OBDParserMode>>& Config::getOBDModeList() const
// {
//     return obdModesList;
// }
//
// This supports both const and non-const contexts.
//
// Usage:
// 
// Modify the list externally
// cfg.getOBDModeList().push_back("Dune");

// Read via const reference
// const Config& cref = cfg;
// for (const auto& b : cref.getOBDModeList())
//     std::cout << b << "\n";
//



std::string Config::toString()
{
	std::string ret = "";

	return ret;
}

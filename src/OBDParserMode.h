/*
 * OBDParserMode.h
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 *
 *  The OBDParserMode is responsible for select right PID for data processing.
 *
 */

#ifndef OBDPARSERMODE_H_
#define OBDPARSERMODE_H_

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "OBDParserModePID.h"


//TODO:
//
// 1.
// If this is base class we need virtual functions here
// Consider, perhaps it should be just only abstract class
//
// 2.
// If this class have a members type pointers to the resources, this class need copy constructor
// and move constructor.


class OBDParserMode
{

public:
	OBDParserMode();
	virtual ~OBDParserMode();

	//OBDParserMode(const OBDParserMode &other);
	//OBDParserMode(OBDParserMode &&other);
	//OBDParserMode& operator=(const OBDParserMode &other);
	//OBDParserMode& operator=(OBDParserMode &&other);

	enum class RetStatus {
	    OK,
	    NOT_OK
	};

    //TODO: Called during app initialization from Config.
    // It should set selected or not this module.
    // And if selected it should load selected PIDs nad select each od them by calling their configure() function
    RetStatus configure(std::vector<std::unique_ptr<OBDParserModePID>> &&PIDsList);

    //virtual std::string getCmdLine() {return CMD_LINE; };
    virtual const char* getCmdLine() {return CMD_LINE; };

    RetStatus processData(std::string& data);

    const std::vector<std::unique_ptr<OBDParserModePID>>& getOBDModePIDsList() const { return modePIDs; };

    virtual std::string toString() {return "I am " + modeName; };


private:
    std::string modeName;
    static constexpr const char* CMD_LINE = "This is a command line from OBDParserMode base class";

    // We have also variant like that
    //class Example {
    //public:
    //  Example() : name("ParserMode01") {}
    //
    //private:
    //    const std::string name;
    //};


    std::vector<std::unique_ptr<OBDParserModePID>> modePIDs;

};

#endif /* OBDPARSERMODE_H_ */

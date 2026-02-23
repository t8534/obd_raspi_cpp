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


//TODO: If this is base class we need virtual functions here
// Consider, perhaps it should be just only abstract class

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

    virtual std::string getCmdLine();

	//TODO: Probably to remove, will be replaced by processingData()
    RetStatus parseData(std::string data);

    RetStatus processingData(std::string& data);

    virtual std::string toString();


private:
    std::string modeName;
    //bool selected = false;  //TODO: this field is probably not necessary as we make list in Config class.
    std::vector<std::unique_ptr<OBDParserModePID>> modePIDs;  //TODO: probably not necessary as we are going to work on the vector declared in Configure class.

};

#endif /* OBDPARSERMODE_H_ */

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
#include <string>
#include <vector>


#include "OBDParserModePID.h"

class OBDParserMode
{

public:
	OBDParserMode();
	virtual ~OBDParserMode();

	//OBDParserMode(const OBDParserMode &other);
	//OBDParserMode(OBDParserMode &&other);
	//OBDParserMode& operator=(const OBDParserMode &other);
	//OBDParserMode& operator=(OBDParserMode &&other);

	enum ErrorCode {
	    OK,
	    NOT_OK
	};

    ErrorCode parseData(std::string data);

    //TODO: Called during app initialization from Config.
    // It should set selected or not this module.
    // And if selected it should load selected PIDs nad select each od them by calling their configure() function
    ErrorCode configure(bool modeSelected, std::vector &PIDsList);

    std::string toString();


private:
    std::string modeName;
    bool selected = false;
    std::vector<OBDParserModePID> modePIDs;


};

#endif /* OBDPARSERMODE_H_ */

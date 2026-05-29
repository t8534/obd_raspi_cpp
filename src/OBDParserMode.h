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

	// Define template for processing data related to this Mode/PID
	class ResponseDataRecord {
	public:
		virtual ~ResponseDataRecord() {}
		std::string dataBuffer;
		unsigned int timestamp;   //TODO: replace with uint32_t, or whatever for timestamp
		unsigned int gpsCoords;   //TODO: replace with uint32_t, or whatever for gpsCoords
	};

	//TODO: What about this approach in a base class ?
	/*
    class ResponseDataRecord {
    public:
        virtual ~ResponseDataRecord() {}
    };
    */

	enum class RetStatus {
	    OK,
	    NOT_OK
	};

    //TODO: Called during app initialization from Config.
    // It should set selected or not this module.
    // And if selected it should load selected PIDs and select each of them by calling their configure() function
    virtual RetStatus configure(std::vector<std::unique_ptr<OBDParserModePID>> &&PIDsList);

    //virtual std::string getCmdLine() {return CMD_LINE; };
    virtual const char* getCmdLine() {return REQUEST; };
    virtual const unsigned int getResponseLen() {return RESPONSE_LEN; };

    // Parse and process received response data
    virtual RetStatus processData(std::string& data);

    // Return the list of PIDs this Mode contains for processing
    virtual const std::vector<std::unique_ptr<OBDParserModePID>>& getOBDModePIDsList() const { return modePIDs; };

    // Returns the list of currently logged ResponseDataRecors
    virtual const std::vector<std::unique_ptr<ResponseDataRecord>>& getResponseDataRecordList() const { return responseDataRecordList; };

    // Return current ResponseDataRecord
    virtual const ResponseDataRecord& getCurrentResponseDataRecord() const { return currentResponseDataRecord; };

    //TODO: Check the name of the function, make implementation, decide is implementation enough in the base class
    //      or should be in the derived classes.
    //
    //Clear everything needed when new session is started.
    virtual void clearBeforeNewSessionStarted() {};


    virtual std::string toString() {return "I am " + modeName; };


private:
    std::string modeName;
    static constexpr const char* REQUEST = "This is a command line from OBDParserMode base class";
    static constexpr const unsigned int RESPONSE_LEN = 0;   //TODO set correct value, replace unsigned int with uint16_t

    // We have also variant like that
    //class Example {
    //public:
    //  Example() : name("ParserMode01") {}
    //
    //private:
    //    const std::string name;
    //};

    //TODO: How to initialize it on init, and when new session is started ?
    ResponseDataRecord currentResponseDataRecord;

    //TODO: is it necessarry to initialize or empty this vector ? For sure if next session is started, but on first init ?
    std::vector<std::unique_ptr<OBDParserModePID>> modePIDs;

    // Received data are collected here
    // TODO: vector of pointrs or by value ?
    //TODO: is it necessarry to initialize or empty this vector ? For sure if next session is started, but on first init ?
    std::vector<std::unique_ptr<ResponseDataRecord>> responseDataRecordList;

};

#endif /* OBDPARSERMODE_H_ */

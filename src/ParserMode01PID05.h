/*
 * ParserMode01PID05.h
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 */

#ifndef PARSERMODE01PID05_H_
#define PARSERMODE01PID05_H_

#include "OBDParserModePID.h"

class ParserMode01PID05 : public OBDParserModePID
{
public:
	ParserMode01PID05();
	virtual ~ParserMode01PID05();

	//ParserMode01PID05(const ParserMode01PID05 &other);
	//ParserMode01PID05(ParserMode01PID05 &&other);
	//ParserMode01PID05& operator=(const ParserMode01PID05 &other);
	//ParserMode01PID05& operator=(ParserMode01PID05 &&other);

	// Define template for processing data related to this Mode/PID
	class ResponseDataRecord {
	public:
		virtual ~ResponseDataRecord() {}
		unsigned short int engCoolantTemp;  //TODO replace with uint8_t
		unsigned int timestamp;   //TODO: replace with uint32_t, or whatever for timestamp
		unsigned int gpsCoords;   //TODO: replace with uint32_t, or whatever for gpsCoords
	};


	//TODO: is virtual necessary as we were never here a base class for others ?
    //virtual std::string getCmdLine() {return CMD_LINE; };
	virtual const char* getCmdLine() {return REQUEST; };
    virtual const unsigned int getResponseLen() {return RESPONSE_LEN; };

    //TODO: is virtual necessary as we were never here a base class for others ?
    virtual RetStatus processData(std::string& data);

    // Returns the list of currently logged ResponseDataRecors
//    virtual const std::vector<std::unique_ptr<ResponseDataRecord>>& getResponseDataRecordList() const { return responseDataRecordList; };

    // Return current ResponseDataRecord
//    virtual const ResponseDataRecord& getCurrentResponseDataRecord() const { return currentResponseDataRecord; };

    //TODO: Check the name of the function, make implementation, decide is implementation enough in the base class
    //      or should be in the derived classes.
    //Clear everything needed when new session is started.
    virtual void clearBeforeNewSessionStarted() {};


    //TODO: is virtual necessary as we were never here a base class for others ?
    virtual std::string toString() {return pidName; };

private:
    std::string pidName;
    static constexpr const char* REQUEST = "REQUEST Mode01PID05";
    static constexpr const unsigned int RESPONSE_LEN = 1;   //TODO replace unsigned int with uint16_t

    //TODO: How to initialize it on init, and when new session is started ?
    ResponseDataRecord currentResponseDataRecord;

    // Received data are collected here
    // TODO: vector of pointrs or by value ?
    //TODO: is it necessarry to initialize or empty this vector ? For sure if next session is started, but on first init ?
    std::vector<std::unique_ptr<ResponseDataRecord>> responseDataRecordList;

};

#endif /* PARSERMODE01PID05_H_ */


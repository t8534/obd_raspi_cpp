/*
 * OBDParserModePID.h
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 */

#ifndef OBDPARSERMODEPID_H_
#define OBDPARSERMODEPID_H_


#include <iostream>
#include <memory>
#include <string>
#include <vector>


//TODO:
//
// 1.
// If this is base class we need virtual functions here
// Consider, perhaps it should be just only abstract class
//
// 2.
// If this class have a members type pointers to the resources, this class need copy constructor
// and move constructor.
//
// 3.
// Think, is this class should be abstract only, or really base class.
// Because if we have for example vector, not used in derived classes because this is redeclared in there
// we waste a space keeping it here.
//

class OBDParserModePID {
public:
	OBDParserModePID();
	virtual ~OBDParserModePID();


	//OBDParserModePID(const OBDParserModePID &other);
	//OBDParserModePID(OBDParserModePID &&other);
	//OBDParserModePID& operator=(const OBDParserModePID &other);
	//OBDParserModePID& operator=(OBDParserModePID &&other);

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



	//TODO: is this still necessary for PID ?
    virtual RetStatus configure(bool pidSelected);

    //TODO: Replace cmd line with Request
    //TODO: replace getCmdLine() with getRequest()
    //virtual std::string getCmdLine() {return CMD_LINE; };
    virtual const char* getCmdLine() {return REQUEST; };
    virtual const unsigned int getResponseLen() {return RESPONSE_LEN; };

    virtual RetStatus processData(std::string& data);

    // Returns the list of currently logged ResponseDataRecors
    virtual const std::vector<std::unique_ptr<ResponseDataRecord>>& getResponseDataRecordList() const { return responseDataRecordList; };

    // Return current ResponseDataRecord
    virtual const ResponseDataRecord& getCurrentResponseDataRecord() const { return currentResponseDataRecord; };

    //TODO: Check the name of the function, make implementation, decide is implementation enough in the base class
    //      or should be in the derived classes.
    //Clear everything needed when new session is started.
    virtual void clearBeforeNewSessionStarted() {};

    virtual std::string toString() {return "I am " + pidName; };

private:
    std::string pidName;

    static constexpr const char* REQUEST = "This is a command line from OBDParserModePID base class";
    static constexpr const unsigned int RESPONSE_LEN = 0;   //TODO set correct value, replace unsigned int with uint16_t

    //TODO: How to initialize it on init, and when new session is started ?
    ResponseDataRecord currentResponseDataRecord;

    // Received data are collected here
    // TODO: vector of pointrs or by value ?
    //TODO: is it necessarry to initialize or empty this vector ? For sure if next session is started, but on first init ?
    std::vector<std::unique_ptr<ResponseDataRecord>> responseDataRecordList;

};

#endif /* OBDPARSERMODEPID_H_ */

/*
 * OBDParserModePID.h
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 */

#ifndef OBDPARSERMODEPID_H_
#define OBDPARSERMODEPID_H_


#include <iostream>
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


class OBDParserModePID {
public:
	OBDParserModePID();
	virtual ~OBDParserModePID();


	//OBDParserModePID(const OBDParserModePID &other);
	//OBDParserModePID(OBDParserModePID &&other);
	//OBDParserModePID& operator=(const OBDParserModePID &other);
	//OBDParserModePID& operator=(OBDParserModePID &&other);


	enum class RetStatus {
	    OK,
	    NOT_OK
	};

	//TODO: is this still necessary for PID ?
    RetStatus configure(bool pidSelected);

    virtual std::string getCmdLine() {return CMD_LINE; };

	//TODO: Probably to remove, will be replaced by processingData()
    //RetStatus parseData(std::string data);

    virtual RetStatus processData(std::string& data);

    virtual std::string toString() {return "I am " + pidName; };

private:
    std::string pidName;
    static constexpr const char* CMD_LINE = "This is a command line from OBDParserModePID base class";

};

#endif /* OBDPARSERMODEPID_H_ */

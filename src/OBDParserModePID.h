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


class OBDParserModePID {
public:
	OBDParserModePID();
	virtual ~OBDParserModePID();


	//OBDParserModePID(const OBDParserModePID &other);
	//OBDParserModePID(OBDParserModePID &&other);
	//OBDParserModePID& operator=(const OBDParserModePID &other);
	//OBDParserModePID& operator=(OBDParserModePID &&other);


	enum RetStatus {
	    OK,
	    NOT_OK
	};

    RetStatus configure(bool pidSelected);

    RetStatus parseData(std::string data);

    std::string toString();

private:
    std::string pidName;
    bool selected = false;

};

#endif /* OBDPARSERMODEPID_H_ */

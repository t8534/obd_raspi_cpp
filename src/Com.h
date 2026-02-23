/*
 * Com.h
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 */

// AT command set selected for implementation
//
// <CR>    Repeat last command
// D       Set to Defaults
// E0, E1    Echo off or on
// I         Print the version ID
// LP        Go to low power mode
// RD        Read the stored Data byte
// WS        Warm start (soft reset)
// Z         Reset all
// @1        Display the device description
// @2        Display the device identifier
// AR        Automatically Receive
// MA        Monitor all
// IB10      Set the ISO Baud rate to 10400
// IB12      Set the ISO Baud rate to 12500
// IB15      Set the ISO Baud rate to 15625
// IB48      Set the ISO Baud rate to 4800
// IB96      Set the ISO Baud rate to 9600
//



// Error messages and alerts returned by ELM 327
//
// "?"
// "ACT ALERT"
// "!ACT ALERT"
// "BUFFER FULL"
// "BUS BUSY"
// "BUS ERROR"
// "CAN ERROR"
// "DATA ERROR"
// "<DATA ERROR"
// "ERRxx"            This error is ELM internal and should be reported to Elm Electronics, xx is 2 digits.
// "FB ERROR"
// "LP ALERT"
// "!LP ALERT"
// "LV RESET"
// "NO DATA"
// "RX ERROR"
// "STOPPED"
// "UNABLE TO CONNECT"

#ifndef COM_H_
#define COM_H_


#include <string>

class Com {

public:

	Com();
	virtual ~Com();

	enum ErrorCode {
	    OK,
	    NOT_OK
	};

	//Com(const Com &other);
	//Com(Com &&other);
	//Com& operator=(const Com &other);
	//Com& operator=(Com &&other);


	ErrorCode sendCmd(std::string cmd);

	std::string getResponse();

	ErrorCode init();    //TODO: return OK or NOT_OK

	ErrorCode deinit();

	ErrorCode resetHW();    //TODO: return OK or NOT_OK

	ErrorCode resetSW();    //TODO: return OK or NOT_OK


};

#endif /* COM_H_ */

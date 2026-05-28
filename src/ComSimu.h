/*
 * ComSimu.h
 *
 *  Created on: 23 lut 2026
 *      Author: arek1
 *
 * Description:
 * Com simulator.
 *
 *
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


#ifndef COMSIMU_H_
#define COMSIMU_H_

#include <string>

class ComSimu {

public:
	ComSimu();
	virtual ~ComSimu();

	//ComSimu(const ComSimu &other);
	//ComSimu(ComSimu &&other);
	//ComSimu& operator=(const ComSimu &other);
	//ComSimu& operator=(ComSimu &&other);

	enum ErrorCode {
	    OK,
	    NOT_OK
	};

	enum class Command {
	    Mode01Cmd,
		Mode01PID05Cmd,
		Mode01PID11Cmd,
		Mode01PID12Cmd,
		Mode03Cmd,
		UnkownCmc
	};


	//ErrorCode sendCmd(std::string cmd);
	ErrorCode sendCmd(const char* cmdString); // const;

	std::string getResponse();

	ErrorCode init();    //TODO: return OK or NOT_OK

	ErrorCode deinit();

	ErrorCode resetHW();    //TODO: return OK or NOT_OK

	ErrorCode resetSW();    //TODO: return OK or NOT_OK

private:

	//Command parseCommand(const std::string& cmd);
	Command parseCommand(const char* cmd);

	std::string responseBuffer;



};

#endif /* COMSIMU_H_ */

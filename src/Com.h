/*
 * Com.h
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 */

#include <string>

#ifndef COM_H_
#define COM_H_


class Com {

public:

	enum ErrorCode {
	    OK,
	    NOT_OK
	};

	Com();
	virtual ~Com();


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

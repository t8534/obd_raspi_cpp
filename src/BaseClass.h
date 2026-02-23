/*
 * BaseClass.h
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 */

#ifndef BASECLASS_H_
#define BASECLASS_H_

#include <string>

class BaseClass 
{

public:
	BaseClass();
	virtual ~BaseClass();

    //virtual std::string toString() const = 0;
	virtual std::string toString() = 0;

};

#endif /* BASECLASS_H_ */

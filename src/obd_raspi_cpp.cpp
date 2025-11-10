//============================================================================
// Name        : obd_raspi_cpp.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
//
// This is a right file for c++ version
//
//


#include <iostream>
#include "CmdManager.h"

int main() {
	
    std::cout << "Begin " << std::endl; 

    CmdManager cm;
    cm.cyclic(10);

	return 0;
}

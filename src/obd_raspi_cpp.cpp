//============================================================================
// Name        : obd_raspi_cpp.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : This is the main application file
//============================================================================
//
// 
//
//

// TODO:
//
// 1.
// [260307]
// CmdManager.cyclic() is working and collect all CmdLines from OBDMode and OBDModePIDs recursively.
// The next step is update cyclic() to the final way: get cmd line, communicate with ComSimu,
// get response and push it ncak to OBDModes and PIDs.
// Also ComdLine should be replaced with real ones.
// The next step will be processing responses inside of ODBModes and PIDs.
//
// 2. !!!!!!!!!!
// [260527]
// In Makefile:
//     Remove -g below, as this is a hack only.
//     Configure correct Release/Debug options
//


#include <iostream>
#include "Config.h"
//#include "Com.h"
#include "ComSimu.h"
#include "CmdManager.h"

// For test1 test
#include <vector>
#include <memory>
//#include "BaseClass.h"
//#include "Alpha.h"
//#include "Beta.h"


/*
void test1_2(std::vector<std::unique_ptr<BaseClass>> &&bcList)
{
    std::vector<std::unique_ptr<BaseClass>> iList;
    iList = std::move(bcList);

    for (const auto& p : iList)
        std::cout << p->toString() << std::endl; 

}
*/

/*
void test1_1()
{
    std::vector<std::unique_ptr<BaseClass>> baseClassList;
    baseClassList.emplace_back(std::unique_ptr<BaseClass>(new Alpha));
    baseClassList.emplace_back(std::unique_ptr<BaseClass>(new Beta));
    test1_2(std::move(baseClassList));
}
*/

int main() {

	
    std::cout << "Begin " << std::endl; 

    //test1_1();

    Config cfg;
    //Com com;
    ComSimu com;
    //CmdManager cm;
    CmdManager cm(&com);

    if (Config::RetStatus::OK != cfg.configure())
    {
    	std::cout << "Error NOT_OK returned from cfg.configure()" << std::endl;
    	return 0;
    }

    //cm.config(&cfg);
    cm.config(cfg);
    cm.cyclic();


    std::cout << "End " << std::endl; 

	return 0;
}


/*
 * CmdManager.cpp
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 */

#include <iostream> 
#include "CmdManager.h"


//CmdManager::CmdManager() {}

CmdManager::~CmdManager() {}

//CmdManager::CmdManager(const CmdManager &other) {}
//CmdManager::CmdManager(CmdManager &&other) {}
//CmdManager& CmdManager::operator=(const CmdManager &other) {}
//CmdManager& CmdManager::operator=(CmdManager &&other) {}


//  The collaboration with the obd modes list from Config.
//  Seems to be the best option is last one (third) from cpp_notes.txt 1.1 (Option C).
//  Where in CmdManager constructor we set reference to Config.
//  That way we have access to whole public Config not only to the OBDModesList vector.
//  What could be useful for future extensions. Alco coupling is lower as we have no access
//  to the OBDModesList vector that is a member of Config. We have access to whole Config.

void CmdManager::config(const Config& _cfg)
{
	cfg = &_cfg;
}

void CmdManager::cyclic()
{
	// In for() loop:
	// check is OBDMode have PIDs, if so call PIDs sequentially,
	// call OBDModePID getCmdLine from vector,
	// send command to ComSimu,
	// wait for response (can be delayed),
	// handle communication errors,
	// call OBDModePID processData and put the response in there,
	// go to for() loop for next item
	// If OBDMode has no CmdLine you have to detectd it and do not send it to the ELM.
    //

	// The idiom to check is element not null
	/*
    for (const auto& n : modePIDs)
    {
        if (n)
            std::cout << n->toString() << std::endl;
    }
	*/

	// An example for compilation tests
    if (!cfg) return;
    const auto& modes = cfg->getOBDModesList();

    for (const auto& m : modes)
    {
        const char* request = m->getCmdLine();

    	// Request (Command Line) empty means that the Mode has PIDs, so it has no Request itself, like Mode01.
    	// If Mode has no PIDs, like Mode03, than it has Request defined.
    	if (request && request[0] != '\0')  // alternatively: if (request && std::strlen(request) > 0)
    	{
    		//Debug:
    	    //std::cout << "Request of Mode " << m->toString() << " is: " << m->getCmdLine() << std::endl;
    		std::cout << "Request of Mode " << m->toString() << " is: " << request << std::endl;

    		com->sendCmd(request);

    		// Debug
            //Get response from com
            //std::cout << "    Request sent: " <<  m->getCmdLine() << std::endl;
    		std::cout << "    Request sent: " <<  request << std::endl;
            std::cout << "    Response from Com: " << com->getResponse() << std::endl;

    	}

    	// If OBDMode has PIDS walk through them and display their command lines.
        const auto& pidsList = m->getOBDModePIDsList();
        for (const auto& p : pidsList)
        {
        	const char* request = p->getCmdLine();
        	// There should be no PIDs without a Request, but for any case this is a guard.
        	if (request && request[0] != '\0')  // alternatively: if (request && std::strlen(request) > 0)
        	{
        		//Debug
        	    //std::cout << "Request of PID " << p->toString() << " is: " << p->getCmdLine() << std::endl;
        	    std::cout << "Request of PID " << p->toString() << " is: " << request << std::endl;

        	    com->sendCmd(request);

        	    //Debug
                std::cout << "    Request sent: " <<  request << std::endl;
                std::cout << "    Response from Com: " << com->getResponse() << std::endl;
        	}
        }
    }

    //TODO: Print responses  from all, for test.


	std::cout << "I am CmdManager.cyclic() " << std::endl; 

}





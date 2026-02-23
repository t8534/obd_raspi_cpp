/*
 * CmdManager.cpp
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 */

#include <iostream> 
#include "CmdManager.h"

CmdManager::CmdManager() {
	obdModesList = nullptr;
}

CmdManager::~CmdManager() {
	// TODO Auto-generated destructor stub
}


//CmdManager::CmdManager(const CmdManager &other) {}
//CmdManager::CmdManager(CmdManager &&other) {}
//CmdManager& CmdManager::operator=(const CmdManager &other) {}
//CmdManager& CmdManager::operator=(CmdManager &&other) {}


// TODO:
//  1.
//  Should it be unique_ptr here in place of ordinary * ?
//  But I do not want to move ownership.
//  It could be reference, but in general we should avoid references as parameters.
//  But with ordinary pointers it looks bad.
//  ANSWER:
//  Use reference here, see example at cpp_notes.txt

void CmdManager::config(Config& cfg)
{
	//obdModesList = cfg.getOBDModesList();

}

void CmdManager::cyclic()
{

	//TODO: Should it get list of active OBD modes from Config, and processing it ?
	// Or just copy its own from the Config ?

	std::cout << "I am CmdManager.cyclic() " << std::endl; 

}





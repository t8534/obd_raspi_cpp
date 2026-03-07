/*
 * CmdManager.h
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 */

#ifndef CMDMANAGER_H_
#define CMDMANAGER_H_

#include "Config.h"

class CmdManager {
public:
	CmdManager() : cfg(nullptr) {};
	virtual ~CmdManager();


	//CmdManager(const CmdManager &other);
	//CmdManager(CmdManager &&other);
	//CmdManager& operator=(const CmdManager &other);
	//CmdManager& operator=(CmdManager &&other);

	// The config() role is to configure CmdManager before it start processing data
	// in the cyclic() loop. It should be called at application init time, and
	// also if user change a configuration, or set of OBD Modes for processing
	// during app runtime.
    void config(const Config& _cfg);

    void cyclic();


private:

    const Config* cfg;

};

#endif /* CMDMANAGER_H_ */

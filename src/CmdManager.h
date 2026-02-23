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
	CmdManager();
	virtual ~CmdManager();


	//CmdManager(const CmdManager &other);
	//CmdManager(CmdManager &&other);
	//CmdManager& operator=(const CmdManager &other);
	//CmdManager& operator=(CmdManager &&other);

	// The config() role is to configure CmdManager before it start processing data
	// in the cyclic() loop. It should be called at application init time, and
	// also if user change a configuration, or set of OBD Modes for processing
	// during app runtime.
    void config(Config &cfg);

    void cyclic();


private:

    const std::vector<std::unique_ptr<OBDParserMode>> *obdModesList;    //TODO: ordinary pointer or unique_ptr ?

};

#endif /* CMDMANAGER_H_ */

/*
 * CmdManager.h
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 */

#ifndef CMDMANAGER_H_
#define CMDMANAGER_H_

class CmdManager {
public:
	CmdManager();
	virtual ~CmdManager();


	//CmdManager(const CmdManager &other);
	//CmdManager(CmdManager &&other);
	//CmdManager& operator=(const CmdManager &other);
	//CmdManager& operator=(CmdManager &&other);


    void cyclic(int milisec);




};

#endif /* CMDMANAGER_H_ */

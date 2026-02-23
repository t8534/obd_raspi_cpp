/*
 * Config.h
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 *
 *
 *  Description:
 *  The class represents current configuration data, including list of OBD Modes with
 *  their PIDs that should be processed.
 *
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <vector>
#include <memory>
#include <string>

#include "OBDParserMode.h"
#include "OBDParserModePID.h"


class Config {

public:
	Config();
	virtual ~Config();


	//Config(const Config &other);
	//Config(Config &&other);
	//Config& operator=(const Config &other);
	//Config& operator=(Config &&other);


	enum class RetStatus {
	    OK,
	    NOT_OK
	};


    RetStatus configure();

    std::string toString();

	const std::vector<std::unique_ptr<OBDParserMode>>& getOBDModesList() const;


private:
    std::vector<std::unique_ptr<OBDParserMode>> obdModesList;


};

#endif /* CONFIG_H_ */

/*
 * DataLogger.cpp
 *
 *  Created on: 8 lis 2025
 *      Author: arek1
 */

#include "DataLogger.h"


// Example of the file management - RAII
// p.386 Kompendium C++
//
/*
class File_ptr
{

	FILE* p;

public:

	File_ptr(const char* n. const char* a) : p{fopen(n, a)}  // Open the file
	{
		if (p == null_ptr) throw runtime_error{"File_ptr: the file cannot be opened"};
	}

	File_ptr(const string& n. const char* a) : File_ptr{n. c_str(), a} {}  // Open the file

	explicit File_ptr(FILE* pp) : p{pp}  // Przyjecie zalozenia dot. wlasnosci pp
	{
		if (p == null_ptr) throw runtime_error{"File_ptr: nullptr"};
	}

	// odpowiednie operacje przenoszenia i kopiowania

	~File_ptr() { fclose(p); }

	operator FILE*() { return p; }

};
*/


DataLogger::DataLogger() {
	// TODO Auto-generated constructor stub

}

DataLogger::~DataLogger() {
	// TODO Auto-generated destructor stub
}


//DataLogger::DataLogger(const DataLogger &other) {}
//DataLogger::DataLogger(DataLogger &&other) {}
//DataLogger& DataLogger::operator=(const DataLogger &other) {}
//DataLogger& DataLogger::operator=(DataLogger &&other) {}


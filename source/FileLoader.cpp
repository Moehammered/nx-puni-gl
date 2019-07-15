#include "FileLoader.h"

#include <fstream>
#include <sstream>
#include <iostream>

#ifdef USE_EXCEP
#include <stdexcept>
#endif

std::string puni::loadTextFile(std::string path)
{
	std::ifstream fileStream;
	#ifdef USE_EXCEP
	fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try{
		fileStream.open(path);
		std::stringstream fileString;
		fileString << fileStream.rdbuf();
		fileStream.close();

		return fileString.str();
	} 
	catch(std::exception const& e)
	{
		std::cout << "Error occured with exception:\n" << e.what() << std::endl;
	}
	return "";
	#endif
	#ifndef USE_EXCEP
	fileStream.open(path);
	std::stringstream fileString;
	fileString << fileStream.rdbuf();
	fileStream.close();

	return fileString.str();
	#endif
}

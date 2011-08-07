
#include <mlib/logger.hpp>
#include <mlib/datetime.hpp>

#include <iostream>
#include <fstream>

namespace mlib
{
	Logger::Logger(const std::string & filename):file_name(filename){}

	void Logger::log(std::string msg)
	{
		std::fstream file(file_name.c_str(), std::ios::app | std::ios::out);
		std::string date_time = DateTime::now();
		file << date_time << " " ;
		file << msg << std::endl;
		file.close();
	}

}

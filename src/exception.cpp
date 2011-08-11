
#include "mlib/exception.hpp"
#include "mlib/convert.hpp"

namespace mlib
{
	Exception::Exception(std::string message, std::string file, unsigned long long line) : 
	    msg("Error (" + file.substr(file.find_last_of("/\\") + 1) 
	    + ":" + to_str(line, 4, 0, '0') + ") : " + message) {}

	const char * Exception::what() const throw()
	{
		return msg.c_str();
	}
}


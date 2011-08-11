
#include "mlib/exception.hpp"
#include "mlib/convert.hpp"

namespace mlib
{
	Exception::Exception(std::string message, std::string file, unsigned long long line) : 
	    msg("Error (" + file + ":" + to_str(line, 4, 0, '0') + ") : " + message) {}

	std::string Exception::message()
	{
		return msg;
	}
}


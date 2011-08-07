
#ifndef __ILOGGER_HPP__
#define __ILOGGER_HPP__

#include <string>

namespace mlib
{
	class ILogger
	{
		public:
			virtual void log(std::string msg) = 0;
	};
}

#endif


#include <mlib/datetime.hpp>
#include <mlib/convert.hpp>

#include <ctime>
#include <time.h>

namespace mlib
{
	std::string DateTime::now()
	{
		time_t rawtime;
		struct tm * timeinfo;
		time ( &rawtime );
		timeinfo = localtime ( &rawtime );
		std::string date = std::string(to_str(timeinfo->tm_year + 1900) + "." + to_str(timeinfo->tm_mon, 2, 0, '0') + "." + to_str(timeinfo->tm_mday, 2, 0, '0'));
		std::string time = std::string(to_str(timeinfo->tm_hour, 2, 0, '0') + ":" + to_str(timeinfo->tm_min, 2, 0, '0') + ":" + to_str(timeinfo->tm_sec, 2, 0, '0'));
		return std::string (date + " " + time);
	}
}

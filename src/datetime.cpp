
#include <mlib/datetime.hpp>
#include <mlib/convert.hpp>

#include <ctime>
#include <time.h>

namespace mlib
{

	std::ostream & operator <<( std::ostream & stream, const DateTime & dt)
	{
		stream << std::string (dt.date_str() + " " + dt.time_str());
		return stream;
	}

	std::string DateTime::date_str() const
	{
		return std::string(to_str(Y()) + "." + to_str(M(), 2, 0, '0') + "." + to_str(D(), 2, 0, '0'));
	}

	std::string DateTime::time_str() const 
	{
		return std::string(to_str(h(), 2, 0, '0') + ":" + to_str(m(), 2, 0, '0') + ":" + to_str(s(), 2, 0, '0'));
	}

	int DateTime::Y() const 
	{
		return year;
	}

	int DateTime::M() const 
	{
		return month;
	}

	int DateTime::D() const 
	{
		return day;
	}

	int DateTime::h() const 
	{
		return hour;
	}

	int DateTime::m() const 
	{
		return minute;
	}

	int DateTime::s() const 
	{
		return second;
	}

	DateTime::DateTime (int yr, int mt, int dy, int hr, int mn, int sc) : year(yr), month(mt), day(dy), hour(hr), minute(mn), second(sc) {}

	DateTime DateTime::now()
	{
		time_t rawtime;
		struct tm * timeinfo;
		time ( &rawtime );
		timeinfo = localtime ( &rawtime );
		return DateTime(timeinfo->tm_year + 1900, timeinfo->tm_mon, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	}

}


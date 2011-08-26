
#include "mlib/convert.hpp"

namespace mlib
{
	std::string size_to_str(const size_t size_in_byte)
	{
		if (size_in_byte < 1024)
		{
			return to_str(size_in_byte) + " byte";
		}

		double kb = static_cast<double>(size_in_byte) / 1024.0;
		if (kb < 1024.0)
		{
			return to_str(kb, 0, 3) + " Kb";
		}

		double mb = static_cast<double>(size_in_byte) / (1024.0 * 1024.0);
		if (mb < 1024.0)
		{
			return to_str(mb, 0, 3) + " Mb";
		}

		double gb = static_cast<double>(size_in_byte) / (1024.0 * 1024.0 * 1024.0);
		if (gb < 1024.0)
		{
			return to_str(gb, 0, 3) + " Gb";
		}

		double tb = static_cast<double>(size_in_byte) / (1024.0 * 1024.0 * 1024.0 * 1024.0);
		return to_str(tb, 0, 4) + " Tb";
	}

	std::string time_to_str(const double time_in_sec )
	{
		double sec = time_in_sec;
		size_t d = static_cast<size_t>(sec) / 86400;
		sec -= static_cast<double>(d * 86400);

		size_t h = static_cast<size_t>(sec) / 3600;
		sec -= static_cast<double>(h * 3600);

		size_t m = static_cast<size_t>(sec) / 60;
		sec -= static_cast<double>(m * 60);

		return to_str(d) + " days " + to_str(h) + "h " + to_str(m) + "m " + to_str(sec, 0, 6) + "s";
	}
}


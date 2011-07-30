
#include "mlib/progressbar.hpp"

#include <iostream>
#include <iomanip>

namespace mlib
{
	void progress_bar(double progress, std::string msg, size_t len)
	{
		std::cout << "\x1B[2K"; // Erase the entire current line.
		for (size_t i = 0; i < 1024; i++) std::cout << "\b"; // Move to the beginning of the current line.

		if (msg != "")
		{
			std::cout << msg << "\n";
			std::flush(std::cout);
		}

		len -= 10;
		if (progress < 0.0) progress = 0.0;
		if (progress > 1.0) progress = 1.0;

		std::string progress_bar;
		for (size_t i = 0; i < len; ++i)
		{
			if (i < static_cast<int>(len * progress))
			{
				progress_bar += "=";
			}
			else
			{
				progress_bar += " ";
			}
		}

		std::cout << "[" << progress_bar << "] " << std::setiosflags(std::ios::fixed)
				  << std::setprecision(2) << std::setw(6) << progress * 100.0 << "%";

		if (static_cast<int>(progress) == 1) std::cout << "\n";

		std::flush(std::cout);
	}

}



#include <iostream>
#include <string>

#include "mlib/progressbar.hpp"
#include "mlib/convert.hpp"

int main(int argc, const char ** argv)
{
	int max_value = 7;
	for (int i = 0; i <= max_value; i++)
	{
		double progress = static_cast<double>(i) / static_cast<double>(max_value);
		mlib::progress_bar(progress);
		sleep(1);
	}

	for (int i = 0; i <= max_value; i++)
	{
		double progress = static_cast<double>(i) / static_cast<double>(max_value);
		std::string name = "  (CC)  super/mega_file_" + mlib::to_str(i, 3) + ".cpp";
		mlib::progress_bar(progress, name);
		sleep(1);
	}

	return 0;
}

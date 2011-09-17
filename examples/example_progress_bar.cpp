
#include <iostream>
#include <string>

#include "mlib/progressbar.hpp"
#include "mlib/convert.hpp"

int main(int, const char **)
{
	int max_value = 7;
	for (int i = 0; i <= max_value; i++)
	{
		double progress = static_cast<double>(i) / static_cast<double>(max_value);
		mlib::progress_bar(progress);
		mlib::sleep(1);
	}

	for (int i = 0; i <= max_value; i++)
	{
		double progress = static_cast<double>(i) / static_cast<double>(max_value);
		std::string name = "  (CC)  super/mega_file_" + mlib::to_str(i, 3, 0, '0') + ".cpp";
		mlib::progress_bar(progress, name);
		mlib::sleep(1);
	}

	return 0;
}


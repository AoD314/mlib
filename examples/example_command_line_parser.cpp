
#include <iostream>
#include <string>

#include "mlib/command_line_parser.hpp"

using std::cout;
using std::endl;

const std::string keys(
    "{help h usage |  | print help information}"
    "{test t       |20| test value = 20       }"
);

int main(int argc, char ** argv)
{
	mlib::CommandLineParser parser(argc, argv, keys);

	if (parser.has("help"))
	{
		parser.print_help();
		return 0;
	}

	int x = parser.get<int>("test");
	cout << "x = " << x << endl;

	return 0;
}


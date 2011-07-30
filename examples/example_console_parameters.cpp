
#include <iostream>
#include <string>

#include "mlib/console_parameters.hpp"

using std::cout;
using std::endl;

void print_help()
{
	cout << "help info:" << endl;
	cout << "\t-x | --xxx <int>" << endl;
}

int main(int argc, const char ** argv)
{
	mlib::ConsoleParameters params(argc, argv);

	if (params.has(" -h | --help | --usage"))
	{
		print_help();
		return 0;
	}

	int x = params.get("-x | --xxx", 10);
	cout << "x = " << x << endl;

	return 0;
}


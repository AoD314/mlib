
#include <iostream>
#include <string>

#include "mlib/command_line_parser.hpp"

using std::cout;
using std::endl;

const std::string keys(
    "{help h usage |  | print help information     }"
    "{:test t      |20| test value }"
    "{@img         | img.png | path_to_image }"
);

int main(int argc, char ** argv)
{
    mlib::CommandLineParser parser(argc, argv, keys);

    if (parser.has("help"))
    {
        parser.about("CommandLineParser example v0.1");
        parser.print_help();
        return 0;
    }

    int x = parser.get<int>("test");

    if (parser.is_error())
    {
        parser.print_errors();
        return 0;
    }

    cout << "x = " << x << endl;

    return 0;
}

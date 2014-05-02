
#include <iostream>
#include <string>

#include "mlib/convert.hpp"

using std::cout;
using std::endl;

int main(int, const char**)
{
    std::string str = "  101.314614 ";

    int i = mlib::from_str<int>(str);
    double d = mlib::from_str<double>(str);

    cout << "         i = |" << i << "|" << endl;
    cout << "         d = |" << d << "|" << endl;

    cout << " format(i) = |" << mlib::to_str(i, 10, 0, '0') << "|" << endl;
    cout << " format(d) = |" << mlib::to_str(d, 10, 4) << "|" << endl;

    return 0;
}

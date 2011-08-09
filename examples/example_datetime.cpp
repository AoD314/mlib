
#include <iostream>

#include "mlib/datetime.hpp"
#include "mlib/convert.hpp"

using std::cout;
using std::endl;

int main(int argc, const char ** argv)
{
	cout << "Date and Time now is : " << mlib::to_str(mlib::DateTime::now()) << endl;

	mlib::DateTime dt(2000, 3, 3, 12, 13, 8);
	cout << "Other datetime is : " << mlib::to_str(dt) << endl;

	return 0;
}




#include <iostream>
#include <cmath>

#include "mlib/timer.hpp"

void foo(double * arr, size_t n)
{
	for (size_t i1 = 0; i1 < n; i1++)
	for (size_t i2 = 0; i2 < n; i2++)
	for (size_t i3 = 0; i3 < n; i3++)
	for (size_t  j = 0;  j < n; j++)
		arr[j] = sin(static_cast<double>(i1 * i2 * i3 * j));
}

int main(int, const char **)
{
	mlib::Timer timer;

	timer.start();

	size_t size = 64;
	double * arr = new double[size];
	foo(arr, size);
	std::cout << "arr[size / 2] = " << arr[size / 2] << std::endl;

	timer.stop();

	std::cout << "Time : " << timer << std::endl;

	return 0;
}


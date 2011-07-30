
#include <iostream>
#include <cmath>

#include "mlib/timer.hpp"

void foo(double * arr, int n)
{
	for (int i1 = 0; i1 < n; i1++)
	for (int i2 = 0; i2 < n; i2++)
	for (int i3 = 0; i3 < n; i3++)
	for (int j = 0; j < n; j++)
		arr[j] = sin(i1 * i2 * i3 * j);
}

int main(int argc, const char ** argv)
{
	mlib::Timer timer;

	timer.start();

	int size = 64;
	double * arr = new double[size];
	foo(arr, size);
	std::cout << "arr[size / 2] = " << arr[size / 2] << std::endl;

	timer.stop();

	std::cout << "Time : " << timer << std::endl;

	return 0;
}


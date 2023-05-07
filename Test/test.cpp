#include <iostream>
#include <vector>
#include <algorithm>
#include "../MySTL/algorithm.h"

template <typename T>
struct A
{
	T b;
	A() {};
};


int main()
{
	A<int*> a;

	std::cout << a.b << std::endl;

	return 0;
}
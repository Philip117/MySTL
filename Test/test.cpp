#include <iostream>
#include <vector>
#include <algorithm>
#include "../MySTL/algorithm.h"

int main()
{
	int a[5] = { 1,2,3,4,5 };
	std::vector<int> b = { 6,7,8,9,10 };

	std::iter_swap(a, b.begin());
	mystl::iter_swap(a + 1, b.begin()+1);

	return 0;
}
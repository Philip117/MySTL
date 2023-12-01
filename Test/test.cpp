#include <iostream>
#include <vector>
#include "vector.h"
#include <algorithm>
#include "../MySTL/algorithm.h"

class A
{
public:
	A() {};
};

class B
{
public:
	B() {};
};

class C
{
public:
	C() {};
	C(C&) = delete;
};

class D
{
public:
	D() {};
	D(D&) {};
	D& operator=(const D&)= delete;
};

int main()
{
	mystl::vector<A> a;
	mystl::vector<B> b(1);
	mystl::vector<C> c(17);
	mystl::vector<D> d(17);

	return 0;
}
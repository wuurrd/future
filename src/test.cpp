#include "future.h"
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <iostream>
#include <vector>

void getString(const char* str, Result* res)
{
	std::cout << str << std::endl;
}

int main(int argc, char **argv)
{
	Future f;
	Callback a = boost::bind(&getString, "Hello World", _1);
	Callback b = boost::bind(&getString, "Hello Universe", _1);
	Result r(true, 1);
	f.add_callback(a);
	f.callback(&r);
	f.add_callback(b);
	return 1;
}

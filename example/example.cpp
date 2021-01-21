#include <iostream>

#include "../ForLoop_Compile.h"

void add10(int& a)
{
	a += 10;
}

int main()
{
	int a = 10;
	ForLoop_Compile<0, 9>::Loop([&a]() {++a; });
	std::cout << a << std::endl;

	int b = 10;
	ForLoop_Compile<0, 9>::Loop(std::bind(add10, std::ref(b)));
	std::cout << b << std::endl;
}
#include <iostream>
#include "../ForLoop_Compile.h"


void add10(int& a)
{
	a += 10;
}

/// <summary>
/// Loop variable must be at first function argument !!
/// </summary>
/// <param name="loop"></param>
/// <param name="initialValue"></param>
void addLoop(int loop, int initialValue)
{
	std::cout << initialValue + loop << std::endl;
}

int main()
{
	int a = 10;
	ForLoop_Compile<1, 5>::Loop([&a]() {++a; });
	std::cout << a << std::endl;

	ForLoop_Compile<0, 9>::Loop(addLoop, 10);


}
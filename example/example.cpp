#include <iostream>
#include "../ForLoop_Compile.h"

void add10(int& a)
{
	std::cout << a + 10 << std::endl;
}


void addLoop(int loop, int initialValue)
{
	std::cout << initialValue + loop << std::endl;
}

int main()
{
	int a = 0;
	ForLoop_Compile::Loop<1, 5, 2>([&a]() { a += 1; std::cout << a << std::endl;  }); // output : 1, 2, 3

	ForLoop_Compile::LoopWithLoopVariable<0, 9, 1>(addLoop, 10); // output : 10, 11, 12, 13, ... , 19
	//ForLoop_Compile<0, 9>::LoopWithLoopVariable(add10); // ERROR : Loop variable should not be referece
	ForLoop_Compile::LoopWithLoopVariable<0, 10, 2>([](int loopVariable) {std::cout << loopVariable << std::endl; }); // output : 0, 2, 4, 6, 8, 10
}
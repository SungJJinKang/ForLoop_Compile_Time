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

enum class TestEnum : unsigned int
{
	Apple,
	Banana,
	Car,
	Drive

};

int main()
{
	int a = 0;
	ForLoop_CompileTime_Int::Loop<1, 5, 2>([&a]() { a += 1; std::cout << a << std::endl;  }); // output : 1, 2, 3
	ForLoop_CompileTime_Int::LoopWithLoopVariable<0, 9, 1>(addLoop, 10); // output : 10, 11, 12, 13, ... , 19
	//ForLoop_Compile::LoopWithLoopVariable<0, 9, 1>(add10); // ERROR : Loop variable should not be referece
	ForLoop_CompileTime_Int::LoopWithLoopVariable<0, 10, 2>([](int loopVariable) {std::cout << loopVariable << std::endl; }); // output : 0, 2, 4, 6, 8, 10

	ForLoop_CompileTime<TestEnum>::LoopWithLoopVariable<TestEnum::Apple, TestEnum::Drive, 2>([](TestEnum loopVariable)
		{
			switch (loopVariable)
			{
			case TestEnum::Apple:
				std::cout << "Apple" << std::endl;
				break;
			case TestEnum::Banana:
				std::cout << "Banana is yammy" << std::endl;
				break;
			case TestEnum::Car:
				std::cout << "Your Car is nice" << std::endl;
				break;
			case TestEnum::Drive:
				std::cout << "Driving" << std::endl;
				break;
			}
		}
	); // output : Apple, Your Car is nice
}
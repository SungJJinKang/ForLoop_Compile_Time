#include <iostream>
#include "../ForLoop_Compile.h"

template <int value>
constexpr void PrintSquare(int additional)
{
	constexpr int result = value * value; // result is evaluated at compile time
	std::cout << result + additional << std::endl;
}

// Loop Job Functor must have non type template argument to get Loop Variable value at compile time
// And type of non type template argument should equal to Template argument of ForLoop_CompileTime
template<int loopVariable>
struct LoopJobFunctor
{
	constexpr void operator()(int additional)
	{
		PrintSquare<loopVariable>(additional);
	}
};

int main()
{
	ForLoop_CompileTime_Int::LoopWithLoopVariable<0, 10, 1, LoopJobFunctor>(2);
}
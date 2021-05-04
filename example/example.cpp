#include <iostream>

#include "../ForLoop_Compile.h"

enum EnumTest : int
{
	A = 0, 
	B, 
	C, 
	D, 
	E, 
	F, 
	G, 
	H, 
	I, 
	J, 
	K, 
	L, 
	M, 
	N
};

class TempStruct
{
	float a, b, c;
};

template <EnumTest value>
void Function(const TempStruct& tempStruct)
{
	std::cout << static_cast<int>(value) << std::endl;
}

// Loop Job Functor must have non type template argument to get Loop Variable value at compile time
// And type of non type template argument should equal to Template argument of ForLoop_CompileTime
template<EnumTest enumValue>
struct LoopJobFunctor
{
	constexpr void operator()(const TempStruct& tempStruct)
	{
		Function<enumValue>(tempStruct);
	}
};

int main()
{
	TempStruct tmp;

	ForLoop_CompileTime<EnumTest>::Loop<EnumTest::A, EnumTest::N, eConditionType::LT, 1, LoopJobFunctor>(tmp);
	std::cout << std::endl;
	std::cout << std::endl;

	ForLoop_CompileTime<EnumTest>::Loop<EnumTest::N, EnumTest::B, eConditionType::GT, -1, LoopJobFunctor>(tmp);
	std::cout << std::endl;
	std::cout << std::endl;

	//Dont Pass rvalue as argument 
	//ForLoop_CompileTime<EnumTest>::Loop<EnumTest::N, EnumTest::B, eConditionType::GE, -1, LoopJobFunctor>(std::move(tmp));

	/*

	You Can't do this
	for (EnumTest i = EnumTest::A; i <= EnumTest::N; i = static_cast<EnumTest>( static_cast<int>(i) + 1 ) )
	{
		Function<i>();
	}

	or You Should Do this

	Function<EnumTest::A>();
	Function<EnumTest::B>();
	Function<EnumTest::C>();
	Function<EnumTest::D>();
	Function<EnumTest::E>();
	Function<EnumTest::F>();
	Function<EnumTest::G>();
	Function<EnumTest::H>();
	.....

	*/
}
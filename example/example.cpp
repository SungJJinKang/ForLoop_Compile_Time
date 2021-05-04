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

struct TempStruct
{
	float a, b, c;
};

template <EnumTest value>
void Function1(const TempStruct& tempStruct)
{
	std::cout << static_cast<int>(tempStruct.a) << std::endl;
}

template <EnumTest value>
void Function2()
{
	std::cout << "Function2" << std::endl;
}

// Loop Job Functor must have non type template argument to get Loop Variable value at compile time
// And type of non type template argument should equal to Template argument of ForLoop_CompileTime
template<EnumTest enumValue>
struct LoopJobFunctor1
{
	constexpr void operator()(const TempStruct& tempStruct)
	{
		Function1<enumValue>(tempStruct);
	}
};

template<EnumTest enumValue>
struct LoopJobFunctor2
{
	constexpr void operator()()
	{
		Function2<enumValue>();
	}
};

int main()
{
	TempStruct tmp;

	ForLoop_CompileTime<EnumTest>::Loop<EnumTest::A, EnumTest::N, eConditionType::LT, 1, LoopJobFunctor1>(tmp);
	std::cout << std::endl;
	std::cout << std::endl;

	ForLoop_CompileTime<EnumTest>::Loop<EnumTest::N, EnumTest::B, eConditionType::GT, -1, LoopJobFunctor2>();
	std::cout << std::endl;
	std::cout << std::endl;

	//Don't Pass rvalue as argument 
	//ForLoop_CompileTime<EnumTest>::Loop<EnumTest::N, EnumTest::B, eConditionType::GE, -1, LoopJobFunctor1>(std::move(tmp));


	/*

	You Can't do this
	for (EnumTest i = EnumTest::A; i <= EnumTest::N; i = static_cast<EnumTest>( static_cast<int>(i) + 1 ) )
	{
		Function1<i>();
	}

	or You Should Do this

	Function1<EnumTest::A>();
	Function1<EnumTest::B>();
	Function1<EnumTest::C>();
	Function1<EnumTest::D>();
	Function1<EnumTest::E>();
	Function1<EnumTest::F>();
	Function1<EnumTest::G>();
	Function1<EnumTest::H>();
	.....

	*/
}
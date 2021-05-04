# ForLoop_Compile_Time
C++ Compile Time For Loop.

You can use this libary to call iteratelly template function with non type template argument

And Support using enum value as iterate value.

You can evaluate loop variable at compile time!!        

[한국어 블로그](https://sungjjinkang.github.io/c++/2021/01/23/_ForLoopAtCompileTime.html)     

## Feature
  * C++ 17
  * Easy Use
  * Head Only
  * Support Using Enum or Enum class as Iterate value
  * Support Increment value ( maybe std::integer_sequence doesn't support this )
  * Many Example Codes
  
  
## HOW TO USE

Make Functor ( See example ).   
Use ForLoop_CompileTime<EnumTest>::Loop<Loop Start (inclusive), Loop End (inclusive), eCondition_OperatorType ( condition operator type ), Increment Value, LoopJobFunctor>();     
(Maybe C++20 will support template lambda, Then you don't need to make Functior)     

```
Condition operator types ( eCondition_OperatorType ) :         

EQ,  (Equal)      
NEQ, (Not Equal)          
LT,  (Less Than)         
LE,  (Less or Equal)          
GT,  (Greater than)        
GE	 (Greater or Equal)           
```
	
You can use only integer point and enum (enum class) as Loop variable type ( floating type isn't supported on C++17, maybe C++20 support this)     
( passing rvalue reference is undefined behaviour, i'll fix it )


### Using with Enum Type
```c++
enum EnumTest
{
	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P
}

template<EnumTest enumValue>
void Function()
{
	~~~~~~~
}

template<>
void Function<EnumTest::B>()
{
	~~~~~~~
}

template<>
void Function<EnumTest::I>()
{
	~~~~~~~
}

template<>
void Function<EnumTest::O>()
{
	~~~~~~~
}

// Loop Job Functor must have non type template argument to get Loop Variable value at compile time
// And type of non type template argument should equal to Template argument of ForLoop_CompileTime
// C++20 Will Template Lambda, then Yoy will not need this
template<EnumTest enumValue>
struct LoopJobFunctor
{
	constexpr void operator()()
	{
		Function<enumValue>();
	}
};

int main()
{
	//ForLoop_CompileTime<EnumTest>::Loop<Loop Start (inclusive), Loop End (inclusive), eCondition_OperatorType ( condition operator type ), Increment Value, LoopJobFunctor>();
	ForLoop_CompileTime<EnumTest>::Loop<EnumTest::A, EnumTest::N, eCondition_OperatorType::LE, 1, LoopJobFunctor>();
	
	/* 
	
	You Can't do this
	for (EnumTest i = EnumTest::A; i <= EnumTest::N; i = static_cast<EnumTest>( static_cast<int>(i) + 1 ) )
	{
		Function<i>(); // template parameter should be defined at compile-time
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
	Function<EnumTest::I>();
	Function<EnumTest::J>();
	Function<EnumTest::K>();
	Function<EnumTest::L>();
	Function<EnumTest::M>();
	Function<EnumTest::N>();
	.....
	
	*/
}
```

### Using with IntegerType
```c++

// Loop Job Functor must have non type template argument to get Loop Variable value at compile time
// And type of non type template argument should equal to Template argument of ForLoop_CompileTime
template<int loopedValuee>
struct LoopJobFunctor
{
	constexpr void operator()()
	{
		SomethingFunction<loopedValuee>();
	}
};

int main()
{
	ForLoop_CompileTime<int>::Loop<0, 20, eCondition_OperatorType::LE, 2, LoopJobFunctor>();
}
```

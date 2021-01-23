# ForLoop_Compile_Time
C++ Compile Time For Loop.

And Support iterate enum value.

You can evaluate loop variable at compile time!! ( Look Third Function in HOW TO USE  )

## Feature
  * C++ 17
  * Easy Use
  * Support Enum Iterate
  * Many Example Codes
## HOW TO USE



WARNING : 

You can use only integer point and enum (enum class) as Loop variable type ( floating type isn't decided at compile time on C++17, maybe C++20 support this)

```
1.
template <LoopVariableType start, LoopVariableType end, LoopVariableType increment, typename F, typename... Args, std::enable_if_t<start <= end, bool> = true >
static void Loop(F && f, Args&&... args)

: Execute Function for Iterating from start to end 


2.
template <LoopVariableType start, LoopVariableType end, LoopVariableType increment, typename F, typename... Args, std::enable_if_t<start <= end, bool> = true >
static void LoopWithLoopVariable(F&& f, Args&&... args)

: Execute Function ( should have loop variable as first parameter ) for Iterating from start to end 
  Function parameter of LoopWithLoopVariable must have LoopVariableType variable as first function parameter

3.
template <LoopVariableType start, LoopVariableType end, LoopVariableType increment, template<LoopVariableType> typename Functor>
static void LoopWithLoopVariable()

: If You need using Loop Variable evaluated at compile time In Your Loop Job, Use This Function
  You need Template Functor To Use this function

```
### Using Loop Variable Evaluated at compile time In Loop Job
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

// Loop Job Functor must have non type template argument to get Loop Variable value at compile time
// And type of non type template argument should equal to Template argument of ForLoop_CompileTime
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
	ForLoop_CompileTime<EnumTest>::Loop<EnumTest::A, EnumTest::P, 1, LoopJobFunctor>();
	
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
```



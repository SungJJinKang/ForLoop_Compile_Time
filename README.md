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
enum EnumExample
{
	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P
}

template<EnumExample enumValue>
void Function()
{
	~~~~~~~
}

// Loop Job Functor must have non type template argument to get Loop Variable value at compile time
// And type of non type template argument should equal to Template argument of ForLoop_CompileTime
template<EnumExample enumValue>
struct LoopJobFunctor
{
	constexpr void operator()()
	{
		Function<enumValue>();
	}
};

int main()
{
	ForLoop_CompileTime<EnumExample>::LoopWithLoopVariable<EnumExample::A, EnumExample::P, 1, LoopJobFunctor>();
}
```

### Iterate for integer type
```c++
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
	ForLoop_CompileTime_Int::Loop<1, 5, 2>([&a]() { a += 1; std::cout << a << std::endl;  }); // output : 1, 2, 3
	ForLoop_CompileTime_Int::LoopWithLoopVariable<0, 9, 1>(addLoop, 10); // output : 10, 11, 12, 13, ... , 19
	//ForLoop_Compile::LoopWithLoopVariable<0, 9, 1>(add10); // ERROR : Loop variable should not be referece
	ForLoop_CompileTime_Int::LoopWithLoopVariable<0, 10, 2>([](int loopVariable) {std::cout << loopVariable << std::endl; }); // output : 0, 2, 4, 6, 8, 10
}
```

### Iterate for enum type
```c++
enum class TestEnum : unsigned int
{
	Apple,
	Banana,
	Car,
	Drive
};

int main()
{
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
```



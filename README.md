# ForLoop_Compile_Time
C++ Compile Time For Loop.

## Feature
  * C++ 17
  * Easy Use
  
## HOW TO USE

Loop from start(inclusive) to end(inclusive)

If you want loop value is int type, Use ForLoop_Compile::~,
otherwise Use ForLoop_Compile_T<Type>::~ ( example ForLoop_Compile_T<Enum>... )
WARNING : You can use only integer point and enum as Loop variable type ( floating type isn't decided at compile time on C++17, maybe C++20 support this)

1.
ForLoop_Compile::Loop<start, end, increment>(Function, ...)); : Execute Function for Iterating from start to end 

2.
ForLoop_Compile::LoopWithLoopVariable<start, end, increment>(Function, ...)) : Execute Function ( should have loop variable as first parameter ) for Iterating from start to end 


```
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
```

## Will be Supported

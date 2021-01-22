# ForLoop_Compile_Time
C++ Compile Time For Loop.

## Feature
  * C++ 17
  * Template Meta Programming
  
## HOW TO USE
```
Loop from start(inclusive) to end(inclusive)

ForLoop_Compile<start, end>::Loop(std::function<void()>);
ForLoop_Compile<start, end>::Loop(Function, int, ...));
```

```
void add10(int& a);
void addLoop(int loopVariable, int initialValue) // Loop variable must be first argument of loop function
{
	std::cout << initialValue + loopVariable << std::endl; // variable loopVariable will be iterated from 0 to 9 ( inclusive )
}

{
	int a = 10;
	ForLoop_Compile<1, 5>::Loop([&a]() {++a; });
	std::cout << a << std::endl;

	ForLoop_Compile<0, 9>::Loop(addLoop, 10); // -> 10 is passed to second argument ( initialValue ) of function addLoop
}

```

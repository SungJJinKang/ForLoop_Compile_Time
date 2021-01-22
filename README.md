# ForLoop_Compile_Time
C++ Compile Time For Loop.

## HOW TO USE
```
Loop from start(inclusive) to end(inclusive)
ForLoop_Compile<start, end>::Loop(std::function<void()>);
```

```
void add10(int& value);

{
  int a = 10;
  ForLoop_Compile<0, 9>::Loop([&a]() {++a; });

  int b = 10;
  ForLoop_Compile<0, 9>::Loop(std::bind(add10, std::ref(b)
}

```

# Initialize private const array

## Problem

```c++
template<typename T, int N>
struct A {
public:
    A(const T (&a)[N])
    : _a{a}
    {};
private:
    const T _a[N];
};

int main()
{
    A a({1,2,3});
}
```

You can't copy the array in the ctor body, since the array is declared `const`. Array initialization in initialization list is not supported, either.

## Solution

### Use std::array

```c++
#include<array>

template<typename T, size_t N>
class A
{
public:
    A(const std::array<T,N>& arg) : _array{arg} {};
private:
    const std::array<T,N> _array;
};

int main()
{
    A<int,3> a0{{1,2,3}};

    // copy construct from std::array
    std::array std_array{1,2,3};
    A a1{std_array};
    A a2{std::array{1,2,3}};

    // copy construct from c style array
    int c_array[3] {1,2,3};
    A a3{std::array{c_array}};
    A a4{*reinterpret_cast<std::array<int,3>*>(&c_array)};
}
```
[explore](https://godbolt.org/z/B5PZkG)

### Deduce template arguments

```c++
#include<array>
#include<experimental/array>

template<typename T, size_t N>
class A {
public:
    A(const T (&arg)[N]) :_array{std::experimental::to_array(arg)} {};
private:
    const std::array<T,N> _array;
};

int main()
{
    A        a0{{1,2,3}};
    A<int,3> a1{{1,2,3}};

    // copy construct from c style array
    int c_array[3]{1,2,3};
    A a2(c_array);
}
```
[explore](https://godbolt.org/z/XzkTPX)

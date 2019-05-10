# Initialize private const array

## Problem

You can't copy the array in the ctor body, since the array is declared const.

```cpp
struct A {
public:
    A(double d, const std::array<int,N>& a, int i)
    : _d{d}, _a{a}, _i{i}
    {};
private:
    double _d;
    const std::array<int,N> _a;
    int _i;
};

int main()
{
    A<3> a = {3.14, {1,2,3}, 4};
}
```

## Solution

### Use std::array

```c++
#include<array>

template<typename T, size_t N>
class A
{
public:
    A(const std::array<T,N>& arg) : _array{arg} {}; // A
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
[compiler explorer](https://godbolt.org/z/nVcVR7)

### Deduce template arguments

```c++
#include<array>
#include<experimental/array>

template<typename T, size_t N>
class A {
public:
    A(const T (&arg)[N]) :_array{std::experimental::to_array(arg)} {}; // B
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
[compiler explorer](https://godbolt.org/z/Mmk2Iw)

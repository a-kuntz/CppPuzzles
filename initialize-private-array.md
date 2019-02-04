# Initialize private array

## Problem

```cpp
struct A {
public:
    A(double d, const std::array<int,N>& a, int i)
    : _d{d}, _a{a}, _i{i}
    {};
private:
    double _d;
    std::array<int,N> _a;
    int _i;
};

int main()
{
    A<3> a = {3.14, {1,2,3}, 4};
}
```

## Solution

[solution](https://godbolt.org/z/aQYZBs)

```c++
#include<array>
#include<experimental/array>

template<typename T, size_t N>
class A {
public:
    A(const std::array<T,N>& arg) : _array{arg} {}; // A
    A(const T (&arg)[N]) :_array{std::experimental::to_array(arg)} {}; // B
private:
    std::array<T,N> _array;
};

int main()
{
    int array[3] {1,2,3};
    std::array std_array{1,2,3};

    A a1{std_array};
    A a2{std::array{1,2,3}};
    A<int,3> a3{{1,2,3}};
    A a4{std::experimental::to_array(array)};
    A a5{*reinterpret_cast<std::array<int,3>*>(&array)};

    A b1(array);
    A<int,3> b2{{1,2,3}};
    A b3{{1,2,3}};
}
```
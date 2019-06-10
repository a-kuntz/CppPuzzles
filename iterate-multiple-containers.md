# iterate multiple containers simultaneously

## problem

c++11 allows iterating over one container via `for (const auto& itr: container) {}`.
How can one iterate over multiple containers simultaneously?

    for (const auto& [a,b,c] : cont_a, cont_b, cont_c) {...}


## solution using range-v3 zip

```c++
#include <iostream>
#include <vector>
#include <string>
#include <range/v3/view/zip.hpp>

int main()
{
	std::vector<int> const v0 {0, 1, 2, 3, 4};
	std::vector<std::string> const v1 {"a", "b", "c", "d", "e"};

	for (const auto& val : ranges::view::zip(v0, v1))
	{
		std::cout << val.first << ":" << val.second << ", ";
	}
}
```
[explore](https://coliru.stacked-crooked.com/a/cb5eeeec4db23593)

## solution using range-v3 zip_with

```c++
#include <iostream>
#include <vector>
#include <string>
#include <range/v3/view/zip_with.hpp>

int main()
{
	std::vector<std::string> const v0 {"0", "1", "2", "3", "4"};
	std::vector<std::string> const v1 {"a", "b", "c", "d", "e"};

	for (const auto& val : ranges::view::zip_with(std::plus<std::string>{}, v0, v1))
	{
		std::cout << val << ", ";
	}
}
```
[explore](https://coliru.stacked-crooked.com/a/f4605b537172c9d3)

## solution using boost::zip_iterator

```c++
#include <boost/iterator/zip_iterator.hpp>
#include <boost/range.hpp>

template <typename... Containers>
auto zip( Containers&&... containers )
  -> boost::iterator_range <boost::zip_iterator <decltype( boost::make_tuple( std::begin( containers )... ) )> >
{
  auto zip_begin = boost::make_zip_iterator( boost::make_tuple( std::begin( containers )... ) );
  auto zip_end   = boost::make_zip_iterator( boost::make_tuple( std::end(   containers )... ) );
  return boost::make_iterator_range( zip_begin, zip_end );
}

#include <iostream>
#include <set>
#include <vector>

int main()
{
  std::vector <int> xs   = { 2, 3, 5, 7, 11, 13 };
  int               ys[] = { 0, 1, 2, 3,  4,  5 };
  std::set    <int> zs     { 1, 4, 6, 7,  8,  9 };

  for (auto zi : zip( xs, ys, zs ))
  {
    auto [x, y, z] = zi;
    std::cout << "x, y, z = " << x << ", " << y << ", " << z << "\n";
  }
}
```
[source](https://stackoverflow.com/a/8513803/2706707)
[explore](https://coliru.stacked-crooked.com/a/8153f780aadabe21)
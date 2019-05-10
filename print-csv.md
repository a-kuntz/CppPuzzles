# Print comma separated values

## Problem

```c++
#include <iostream>
#include <vector>

int main()
{
	std::vector<int> container { 1, 4, 6, 7,  8,  9 };

	for (const auto& val : container)
	{
		std::cout << val << ", ";
	}
}
```
[explore](https://coliru.stacked-crooked.com/a/232b69b74cf1c421)

## Solution

### Remove trailing chars (hack)

```c++
#include <iostream>
#include <vector>

int main()
{
	std::vector<int> container { 1, 4, 6, 7,  8,  9 };

	for (const auto& val : container)
	{
		std::cout << val << ", ";
	}
	std::cout << "\b\b";
}
```
[explore](https://coliru.stacked-crooked.com/a/232b69b74cf1c421)

This is only working when text is displayed to terminal.

### Use curried objects

```c++
#include <iostream>
#include <vector>
#include <string>

class Printer
{
public:
	explicit Printer(std::ostream& out, const std::string& sep)
	: _first(true)
	, _out(out)
	, _sep(sep)
	{}

	template <typename T>
	friend Printer& operator<<(Printer& printer, const T& value)
	{
		if (printer._first)
		{
			printer._first = false;
		}
		else
		{
			printer._out << printer._sep;
		}

		printer._out << value;
		return printer;
	}

private:
	bool _first;
	std::ostream& _out;
	const std::string _sep;
};

int main()
{
	std::vector<int> container { 1, 4, 6, 7,  8,  9 };

	Printer printer{std::cout, ","};

	for (const auto& val : container)
	{
		printer << val;
	}
}
```
[source](https://www.fluentcpp.com/2019/05/07/output-strings-separated-commas-cpp/)
[explore](https://onlinegdb.com/SkkuZYX3N)

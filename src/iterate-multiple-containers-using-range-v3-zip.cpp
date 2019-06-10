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

	std::cout << std::endl;
}

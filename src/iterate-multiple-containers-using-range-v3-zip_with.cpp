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
	std::cout << std::endl;
}
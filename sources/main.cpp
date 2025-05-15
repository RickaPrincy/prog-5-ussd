#include <iostream>
#include <ussd/ussd.hpp>

auto main(int argc, char *argv[]) -> int
{
	std::cout << ussd::sum(2, 5) << "\n";
	return 0;
}

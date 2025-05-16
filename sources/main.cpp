#include <ussd/option.hpp>

#include "root.hpp"

auto main() -> int
{
	auto is_running = true;
	auto root = ussd::create_root_menu(is_running);
	auto *current = &root;

	current->print();
	return 0;
}

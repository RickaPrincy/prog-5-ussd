#include "option.hpp"
#include "root.hpp"
#include "utils.hpp"

auto main() -> int
{
	auto is_running = true;
	auto root = ussd::create_root_menu(is_running);
	auto current = &root;

	while (is_running)
	{
		if (current->get_childs()->empty())
		{
			break;
		}

		current->print();
		auto user_reponse = ussd::get_choice_from_option(current);
		if (ussd::handle_special_resonse(user_reponse, is_running, current))
		{
			continue;
		}

		current = current->select_child(user_reponse);
	}
	return 0;
}

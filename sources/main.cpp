#include <csignal>
#include <iostream>
#include <stdexcept>

#include "option.hpp"
#include "static_options.hpp"

// TO handle ctrl + c or something else that can stop the application
static auto is_running = true;
static void signal_handler(int signal)
{
	is_running = false;
}

auto main() -> int
{
	std::signal(SIGINT, signal_handler);

	ussd::Option *current = nullptr;
	auto root = ussd::create_root_menu(current, is_running);
	current = &root;

	while (is_running)
	{
		if (current->get_childs()->empty())
		{
			break;
		}

		current->print();

		try
		{
			auto user_choice = current->ask_choices(current, is_running);
			auto choosed_option = current->select_child(user_choice);
			if (choosed_option->get_childs()->empty())
			{
				continue;
			}
			current = choosed_option;
		}
		catch (std::runtime_error &e)
		{
			std::cout << "Oouch timeout reached !!" << "\n";
			break;
		}
	}
	return 0;
}

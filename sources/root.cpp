#include "root.hpp"

#include <iostream>
#include <ussd/option.hpp>

namespace ussd
{
	auto create_root_menu(bool &is_running) -> Option
	{
		return Option("Main Menu",
			{ Option("Balance", [] { std::cout << "Checking balance...\n"; }),
				Option("Recharge", [] { std::cout << "Recharging...\n"; }),
				Option("Settings",
					{ Option("Language", [] { std::cout << "Changing language...\n"; }),
						Option("PIN", [] { std::cout << "Changing PIN...\n"; }) }),
				Option("Exit", [&is_running] { is_running = false; }) });
	}
}  // namespace ussd

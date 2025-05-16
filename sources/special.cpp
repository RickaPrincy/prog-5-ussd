#include "special.hpp"

#include <iostream>

namespace ussd
{
	auto SpecialOption::exit(bool &is_running) -> Option *
	{
		return new Option("0",
			"Quitter",
			[&]()
			{
				is_running = false;
				std::cout << "<-- VELOMA (-_-!) VELOMA -->" << "\n";
			});
	}

	auto SpecialOption::back(Option *&current) -> Option *
	{
		return new Option("*", "Retour", [&]() { current = current->get_parent(); });
	}

	auto SpecialOption::root(Option *&current) -> Option *
	{
		return new Option("**", "Accueil", [&]() { current = current->get_root(); });
	}
}  // namespace ussd

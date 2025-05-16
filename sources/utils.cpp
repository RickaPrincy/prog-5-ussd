#include "utils.hpp"

#include <algorithm>
#include <iterator>
#include <rcli/inputs.hpp>
#include <string>
#include <vector>

namespace ussd
{

	const std::string SpecialOption::ROOT_LABEL = "Accueil";
	const std::string SpecialOption::EXIT_LABEL = "Quitter";
	const std::string SpecialOption::BACK_LABEL = "Retour";
	constexpr size_t BACK_POSITION = 1;

	rcli::InputConfig config = rcli::InputConfig().clean(true).required(true);
	auto get_choice_from_option(Option *option) -> std::string
	{
		std::vector<std::string> choices{};

		std::transform(option->get_childs()->begin(),
			option->get_childs()->end(),
			std::back_inserter(choices),
			[](Option *child) { return child->get_label(); });

		if (option->get_parent() != nullptr)
		{
			choices.insert(choices.begin(), SpecialOption::ROOT_LABEL);
			choices.insert(choices.begin() + BACK_POSITION, SpecialOption::BACK_LABEL);
		}

		choices.emplace_back(SpecialOption::EXIT_LABEL);
		return rcli::ask_value_in_list_as_number("", choices);
	}

	auto handle_special_resonse(const std::string &response, bool &is_running, Option *&current)
		-> bool
	{
		static const std::unordered_map<std::string, std::function<void(Option *)>> actions = {
			{ SpecialOption::ROOT_LABEL, [&](Option *opt) { current = opt->get_root(); } },
			{ SpecialOption::EXIT_LABEL, [&](Option *opt) { is_running = false; } },
			{ SpecialOption::BACK_LABEL,
				[&](Option *opt)
				{
					if (opt->get_parent() == nullptr)
					{
						return;
					}
					current = opt->get_parent();
				} }
		};

		auto it = actions.find(response);
		if (it == actions.end())
		{
			return false;
		}

		it->second(current);
		return true;
	}
}  // namespace ussd

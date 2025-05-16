#pragma once

#include "option.hpp"

namespace ussd
{
	class SpecialOption
	{
	public:
		static const std::string ROOT_LABEL;
		static const std::string BACK_LABEL;
		static const std::string EXIT_LABEL;
	};

	auto get_choice_from_option(Option *option) -> std::string;
	auto handle_special_resonse(const std::string &response, bool &is_running, Option *&current)
		-> bool;
}  // namespace ussd

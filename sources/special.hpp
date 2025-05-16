#pragma once

#include "option.hpp"

namespace ussd
{
	auto init_special_options(Option *&current, bool &is_running) -> void;
	namespace SpecialOption
	{
		auto exit(bool &is_running) -> Option *;
		auto back(Option *&current) -> Option *;
		auto root(Option *&current) -> Option *;
	}  // namespace SpecialOption
}  // namespace ussd

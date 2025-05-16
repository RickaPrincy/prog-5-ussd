#include "option.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <rcli/inputs.hpp>
#include <stdexcept>
#include <string>
#include <utility>

#include "utils.hpp"

namespace ussd
{
	static const auto INPUT_TIMEOUT = std::chrono::seconds(10);
	static rcli::InputConfig config = rcli::InputConfig().clean(true).required(true);

	Option::Option(std::string id, std::string label, std::vector<Option *> childs)
		: m_childs(std::move(childs)),
		  m_label(std::move(label)),
		  m_id(std::move(id))
	{
		std::for_each(this->m_childs.begin(),
			this->m_childs.end(),
			[&](Option *child) { child->p_parent = this; });
	}

	Option::Option(std::string id, std::string label, Callback callback)
		: m_callback(std::move(callback)),
		  m_label(std::move(label)),
		  m_id(std::move(id))
	{
		std::for_each(this->m_childs.begin(),
			this->m_childs.end(),
			[&](Option *child) { child->p_parent = this; });
	}

	auto Option::get_root() -> Option *
	{
		if (this->p_parent == nullptr)
		{
			return this;
		}

		return this->p_parent->get_root();
	}

	auto Option::get_childs() -> std::vector<Option *> *
	{
		return &this->m_childs;
	}

	auto Option::get_parent() -> Option *
	{
		if (this->p_parent == nullptr)
		{
			return this;
		}

		return this->p_parent;
	}

	auto Option::select_child(std::string id) -> Option *
	{
		auto it = std::find_if(this->m_childs.begin(),
			this->m_childs.end(),
			[&](Option *child) { return id == child->get_id(); });

		if (it == this->m_childs.end())
		{
			throw std::runtime_error("Unexpected Value");
		}

		(*it)->m_callback();
		return *it;
	}

	auto Option::print() -> void
	{
		std::cout << "\n=== " << this->get_label() << " ===\n";
		std::for_each(this->m_childs.begin(),
			this->m_childs.end(),
			[&](Option *child) { std::cout << child->m_id << ". " << child->m_label << "\n"; });
	}

	auto Option::get_label() -> std::string
	{
		return this->m_label;
	}

	auto Option::get_id() -> std::string
	{
		return this->m_id;
	}

	Option::~Option()
	{
		std::for_each(
			this->m_childs.begin(), this->m_childs.end(), [&](Option *child) { delete child; });
	}

	auto Option::ask_choices(Option *&current, bool &is_running) -> std::string
	{
		std::vector<std::string> choices{};
		std::transform(this->m_childs.begin(),
			this->m_childs.end(),
			std::back_inserter(choices),
			[&](Option *child) { return child->get_id(); });

		auto result = ussd::execute_with_timeout<std::string>(
			[&]() { return rcli::ask_value_in_list(config, choices); }, INPUT_TIMEOUT);

		if (!result.has_value())
		{
			throw std::runtime_error("Timeouuuuuuuuuuuuuuuuut xD");
		}
		return result.value();
	}

	auto Option::execute_callback() -> void
	{
		this->m_callback();
	}
}  // namespace ussd

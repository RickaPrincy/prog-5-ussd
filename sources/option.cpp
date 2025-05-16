#include "option.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <utility>

namespace ussd
{
	Option::Option(std::string label, std::vector<Option *> childs)
		: m_childs(std::move(childs)),
		  m_label(std::move(label))
	{
		std::for_each(this->m_childs.begin(),
			this->m_childs.end(),
			[&](Option *child) { child->p_parent = this; });
	}

	Option::Option(std::string label, Callback callback)
		: m_callback(std::move(callback)),
		  m_label(std::move(label))
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
		return this->p_parent;
	}

	auto Option::select_child(std::string &label) -> Option *
	{
		auto it = std::find_if(this->m_childs.begin(),
			this->m_childs.end(),
			[&](Option *child) { return label == child->get_label(); });

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
	}

	auto Option::get_label() -> std::string
	{
		return this->m_label;
	}

	Option::~Option()
	{
		std::for_each(
			this->m_childs.begin(), this->m_childs.end(), [&](Option *child) { delete child; });
	}
}  // namespace ussd

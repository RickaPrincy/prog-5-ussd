#include <algorithm>
#include <iostream>
#include <ussd/option.hpp>
#include <utility>

namespace ussd
{
	Option::Option(std::string label, std::vector<Option> childs)
		: m_childs(std::move(childs)),
		  m_label(std::move(label))
	{
		std::for_each(this->m_childs.begin(),
			this->m_childs.end(),
			[&](Option &child) { child.p_parent = this; });
	}

	Option::Option(std::string label, Callback callback)
		: m_callback(std::move(callback)),
		  m_label(std::move(label))
	{
		std::for_each(this->m_childs.begin(),
			this->m_childs.end(),
			[&](Option &child) { child.p_parent = this; });
	}

	auto Option::get_root() -> Option *
	{
		if (this->p_parent == nullptr)
		{
			return this;
		}

		return this->p_parent->get_root();
	}

	auto Option::get_childs() -> std::vector<Option>
	{
		return this->m_childs;
	}

	auto Option::get_parent() -> Option *
	{
		return this->p_parent;
	}

	auto Option::select_child(int index) -> Option *
	{
		if (this->m_childs.size() <= index)
		{
			return this;
		}

		Option *selected = &m_childs[index];
		selected->m_callback();
		return selected;
	}

	auto Option::print() -> void
	{
		std::cout << "\n=== " << this->get_label() << " ===\n";
		std::cout << "Choose an option (or -1 to go back): \n";

		for (size_t i = 0; i < this->get_childs().size(); ++i)
		{
			std::cout << i << ". " << this->get_childs().at(i).get_label() << "\n";
		}
	}

	auto Option::get_label() -> std::string
	{
		return this->m_label;
	}
}  // namespace ussd

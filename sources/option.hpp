#pragma once

#include <functional>
#include <string>
#include <vector>

namespace ussd
{
	using Callback = std::function<void()>;

	class Option
	{
	private:
		std::string m_label{};
		Option* p_parent = nullptr;
		std::vector<Option*> m_childs{};
		Callback m_callback = []() { };

	public:
		Option(std::string label, Callback callback);
		Option(std::string label, std::vector<Option*> m_childs);
		virtual ~Option();

		auto get_label() -> std::string;
		auto get_parent() -> Option*;
		auto get_root() -> Option*;
		auto get_childs() -> std::vector<Option*>*;
		auto select_child(std::string& label) -> Option*;
		virtual auto print() -> void;
	};
}  // namespace ussd

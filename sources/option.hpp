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
		std::string m_id{};
		Option *p_parent = nullptr;
		std::vector<Option *> m_childs{};
		// clang-format off
    Callback m_callback = []() {};
		// clang-format on

	public:
		Option(std::string id, std::string label, Callback callback);
		Option(std::string id, std::string label, std::vector<Option *> m_childs);
		virtual ~Option();
		virtual auto ask_choices(Option *&current, bool &is_running) -> std::string;
		virtual auto print() -> void;
		virtual auto execute_callback() -> void;

		auto get_label() -> std::string;
		auto get_parent() -> Option *;
		auto get_id() -> std::string;
		auto get_root() -> Option *;
		auto get_childs() -> std::vector<Option *> *;
		auto select_child(std::string id) -> Option *;
	};
}  // namespace ussd

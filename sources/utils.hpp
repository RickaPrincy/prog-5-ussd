#pragma once

#include <chrono>
#include <future>
#include <optional>

namespace ussd
{

	template<typename T>
	auto execute_with_timeout(std::function<T()> func, std::chrono::seconds timeout)  // NOLINT
		-> std::optional<T>
	{
		auto future = std::async(std::launch::async, func);
		if (future.wait_for(timeout) == std::future_status::ready)
		{
			return future.get();
		}
		else
		{
			return std::nullopt;
		}
	}
}  // namespace ussd

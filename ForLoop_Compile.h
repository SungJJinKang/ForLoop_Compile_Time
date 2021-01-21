#pragma once
#include <functional>

/// <summary>
/// loop from start(inclusive) to end(inclusive)
/// </summary>
template <size_t start, size_t end>
struct ForLoop_Compile
{
	static_assert(start <= end, "end must be greater than start");
	static void Loop(const std::function<void()>& job)
	{
		job();

		if constexpr (start < end)
		{
			ForLoop_Compile<start + 1, end>::Loop(job);
		}
	}
};
#pragma once
#include <functional>
#include <utility>
#include <type_traits>
/// <summary>
/// loop from start(inclusive) to end(inclusive)
/// </summary>
template <typename T, std::enable_if_t<std::is_integral_v<T> || std::is_enum_v<T>, bool> = true>
struct ForLoop_Compile_T
{
	template <T start, T end, T increment, typename F, typename... Args >
	static void Loop(F && f, Args&&... args)
	{
		static_assert(start <= end, "end must be greater than start");
		std::invoke(std::forward<F>(f), std::forward<Args>(args)...);

		if constexpr (start + increment <= end)
		{
			Loop<start + increment, end, increment>(std::forward<F>(f), std::forward<Args>(args)...);
		}
	}

	template <T start, T end, T increment, typename F, typename... Args >
	static void LoopWithLoopVariable(F&& f, Args&&... args)
	{
		static_assert(start <= end, "end must be greater than start");
		std::invoke(std::forward<F>(f), start, std::forward<Args>(args)...);

		if constexpr (start + increment <= end)
		{
			LoopWithLoopVariable<start + increment, end, increment>(std::forward<F>(f), std::forward<Args>(args)...);
		}
	}

};

using ForLoop_Compile = typename ForLoop_Compile_T<int>;
using ForLoop_Compile_UnsignedInt = typename ForLoop_Compile_T<unsigned int>;
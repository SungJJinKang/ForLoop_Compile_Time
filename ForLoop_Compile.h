#pragma once
#include <functional>
#include <utility>
#include <type_traits>

template <typename LoopVariableType, typename DUMMY = void> struct ForLoop_CompileTime;

/// <summary>
/// if Loop variable is integer type
/// loop from start(inclusive) to end(inclusive)
/// </summary>
template <typename LoopVariableType>
struct ForLoop_CompileTime<typename LoopVariableType, std::enable_if_t<std::is_integral_v<LoopVariableType>> >
{
	template <LoopVariableType start, LoopVariableType end, LoopVariableType increment, typename F, typename... Args, std::enable_if_t<start <= end, bool> = true >
	static void Loop(F && f, Args&&... args)
	{
		std::invoke(std::forward<F>(f), std::forward<Args>(args)...);

		if constexpr (start + increment <= end)
		{
			Loop<start + increment, end, increment>(std::forward<F>(f), std::forward<Args>(args)...);
		}
	}

	template <LoopVariableType start, LoopVariableType end, LoopVariableType increment, typename F, typename... Args, std::enable_if_t<start <= end, bool> = true  >
	static void LoopWithLoopVariable(F&& f, Args&&... args)
	{
		std::invoke(std::forward<F>(f), start, std::forward<Args>(args)...);

		if constexpr (start + increment <= end)
		{
			LoopWithLoopVariable<start + increment, end, increment>(std::forward<F>(f), std::forward<Args>(args)...);
		}
	}

	template <LoopVariableType start, LoopVariableType end, LoopVariableType increment, template<LoopVariableType> typename Functor, typename... Args, std::enable_if_t<start <= end, bool> = true >
	static void LoopWithLoopVariable(Args&&... args)
	{
		Functor<start>()(std::forward<Args>(args)...);

		if constexpr (start + increment <= end)
		{
			LoopWithLoopVariable<start + increment, end, increment, Functor>(std::forward<Args>(args)...);
		}
	}
};


/// <summary>
/// if Loop variable is enum or enum class type
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename LoopVariableType>
struct ForLoop_CompileTime<typename LoopVariableType, std::enable_if_t<std::is_enum_v<LoopVariableType>> >
{
	using enum_underlying_type = std::underlying_type_t<LoopVariableType>;

	template <LoopVariableType start, LoopVariableType end, typename enum_underlying_type increment, typename F, typename... Args, std::enable_if_t<start <= end, bool> = true  >
	static void Loop(F&& f, Args&&... args)
	{
		std::invoke(std::forward<F>(f), std::forward<Args>(args)...);

		if constexpr (static_cast<enum_underlying_type>(start) + increment <= static_cast<enum_underlying_type>(end) )
		{
			Loop<start + increment, end, increment>(std::forward<F>(f), std::forward<Args>(args)...);
		}
	}

	template <LoopVariableType start, LoopVariableType end, typename enum_underlying_type increment, typename F, typename... Args, std::enable_if_t<start <= end, bool> = true  >
	static void LoopWithLoopVariable(F&& f, Args&&... args)
	{
		std::invoke(std::forward<F>(f), start, std::forward<Args>(args)...);

		if constexpr (static_cast<enum_underlying_type>(start) + increment <= static_cast<enum_underlying_type>(end) )
		{
			LoopWithLoopVariable< static_cast<LoopVariableType>( static_cast<enum_underlying_type>(start) + increment ), end, increment>(std::forward<F>(f), std::forward<Args>(args)...);
		}
	}

	template <LoopVariableType start, LoopVariableType end, typename enum_underlying_type increment, template<LoopVariableType> typename Functor, typename... Args, std::enable_if_t<start <= end, bool> = true >
	static void LoopWithLoopVariable(Args&&... args)
	{
		Functor<start>()(std::forward<Args>(args)...);

		if constexpr (static_cast<enum_underlying_type>(start) + increment <= static_cast<enum_underlying_type>(end))
		{
			LoopWithLoopVariable<static_cast<LoopVariableType>(static_cast<enum_underlying_type>(start) + increment), end, increment, Functor>(std::forward<Args>(args)...);
		}
	}
};


using ForLoop_CompileTime_Int = typename ForLoop_CompileTime<int>;
using ForLoop_CompileTime_UnsignedInt = typename ForLoop_CompileTime<unsigned int>;

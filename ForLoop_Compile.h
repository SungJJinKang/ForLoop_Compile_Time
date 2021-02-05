#pragma once
#include <functional>
#include <utility>
#include <type_traits>


template <typename LoopVariableType, typename DUMMY = void> struct ForLoop_CompileTime;

template <typename T>
using if_rvalue_reference_change_to_lvalue_reference = std::conditional_t<!std::is_reference_v<T>, T, std::conditional_t<std::is_lvalue_reference_v<T>, T, std::add_lvalue_reference_t<T>>>;

#include <iostream>

/// <summary>
/// if Loop variable is integer type
/// loop from start(inclusive) to end(inclusive)
/// </summary>
template <typename LoopVariableType>
struct ForLoop_CompileTime<typename LoopVariableType, std::enable_if_t<std::is_integral_v<LoopVariableType>> >
{
	template <LoopVariableType start, LoopVariableType end, LoopVariableType increment, template<LoopVariableType> typename Functor, typename... Args, std::enable_if_t<start <= end, bool> = true >
	static void Loop(Args&&... args)
	{
		// TODO : Support rvalue reference, 
		// First, make object through move sement with passed rvalue reference in First Loop Function
		// Second, pass maked object to Functor
		// Third, pass maked object to next loop as lvalue reference
		// 
		// for Looping, just one object will be used through lvalue reference
		//
		// use decltype to find check rvalue reference
		// 

		Functor<start>()(std::forward<Args>(args)...);

		if constexpr (start + increment <= end)
		{
			Loop<start + increment, end, increment, Functor>(std::forward<Args>(args)...);
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

	template <LoopVariableType start, LoopVariableType end, typename enum_underlying_type increment, template<LoopVariableType> typename Functor, typename... Args, std::enable_if_t<start <= end, bool> = true >
	static void Loop(Args&&... args)
	{
		
		Functor<start>()(std::forward<Args>(args)...);

		if constexpr (static_cast<enum_underlying_type>(start) + increment <= static_cast<enum_underlying_type>(end))
		{
			Loop<static_cast<LoopVariableType>(static_cast<enum_underlying_type>(start) + increment), end, increment, Functor>(std::forward<Args>(args)...);
		}
	}
};


using ForLoop_CompileTime_Int = typename ForLoop_CompileTime<int>;
using ForLoop_CompileTime_UnsignedInt = typename ForLoop_CompileTime<unsigned int>;

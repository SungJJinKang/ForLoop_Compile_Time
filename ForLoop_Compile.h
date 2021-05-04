#pragma once
#include <functional>
#include <utility>
#include <type_traits>


template <typename LoopVariableType, typename DUMMY = void> struct ForLoop_CompileTime;

template <typename T>
using if_rvalue_reference_change_to_lvalue_reference = std::conditional_t<!std::is_reference_v<T>, T, std::conditional_t<std::is_lvalue_reference_v<T>, T, std::add_lvalue_reference_t<T>>>;

#include <iostream>

enum class eCondition_OperatorType
{
	Eqaul,
	NotEqual,
	SmallerThan,
	SmallerThanOrEqual,
	BiggerThan,
	BIggerThanOrEqual
};

/// <summary>
/// if Loop variable is integer type
/// loop from start(inclusive) to end(inclusive)
/// </summary>
template <typename LoopVariableType>
struct ForLoop_CompileTime<typename LoopVariableType, std::enable_if_t<std::is_integral_v<LoopVariableType>> >
{
	template <LoopVariableType start, LoopVariableType condition, eCondition_OperatorType condition_operator_type, LoopVariableType increment, template<LoopVariableType> typename Functor, typename... Args>
	static void Loop(Args&... args)
	{
		static_assert(!std::is_rvalue_reference_v<Args>...);

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


		if constexpr (
			(condition_operator_type == eCondition_OperatorType::Eqaul && start + increment == condition) ||
			(condition_operator_type == eCondition_OperatorType::NotEqual && start + increment != condition) ||
			(condition_operator_type == eCondition_OperatorType::SmallerThan && start + increment < condition) ||
			(condition_operator_type == eCondition_OperatorType::SmallerThanOrEqual && start + increment <= condition) ||
			(condition_operator_type == eCondition_OperatorType::BiggerThan && start + increment > condition) ||
			(condition_operator_type == eCondition_OperatorType::BIggerThanOrEqual && start + increment >= condition)
		)
		{
			Loop<start + increment, condition, condition_operator_type, increment, Functor>(std::forward<Args>(args)...);
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

	template <LoopVariableType start, LoopVariableType condition, eCondition_OperatorType condition_operator_type, typename enum_underlying_type increment, template<LoopVariableType> typename Functor, typename... Args>
	static void Loop(Args&... args)
	{
		static_assert(!std::is_rvalue_reference_v<Args>...);

		Functor<start>()(std::forward<Args>(args)...);

		if constexpr (
			(condition_operator_type == eCondition_OperatorType::Eqaul && static_cast<enum_underlying_type>(start) + increment == static_cast<enum_underlying_type>(condition)) ||
			(condition_operator_type == eCondition_OperatorType::NotEqual && static_cast<enum_underlying_type>(start) + increment != static_cast<enum_underlying_type>(condition)) ||
			(condition_operator_type == eCondition_OperatorType::SmallerThan && static_cast<enum_underlying_type>(start) + increment < static_cast<enum_underlying_type>(condition)) ||
			(condition_operator_type == eCondition_OperatorType::SmallerThanOrEqual && static_cast<enum_underlying_type>(start) + increment <= static_cast<enum_underlying_type>(condition)) ||
			(condition_operator_type == eCondition_OperatorType::SmallerThanOrEqual && static_cast<enum_underlying_type>(start) + increment <= static_cast<enum_underlying_type>(condition)) ||
			(condition_operator_type == eCondition_OperatorType::BiggerThan && static_cast<enum_underlying_type>(start) + increment > static_cast<enum_underlying_type>(condition)) ||
			(condition_operator_type == eCondition_OperatorType::BIggerThanOrEqual && static_cast<enum_underlying_type>(start) + increment >= static_cast<enum_underlying_type>(condition))
			)
		{
			Loop<static_cast<LoopVariableType>(static_cast<enum_underlying_type>(start) + increment), condition, condition_operator_type, increment, Functor>(std::forward<Args>(args)...);
		}
	}
};


using ForLoop_CompileTime_Int = typename ForLoop_CompileTime<int>;
using ForLoop_CompileTime_UnsignedInt = typename ForLoop_CompileTime<unsigned int>;

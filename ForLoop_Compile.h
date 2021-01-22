#pragma once
#include <functional>
#include <utility>
#include <type_traits>
/// <summary>
/// loop from start(inclusive) to end(inclusive)
/// </summary>
template <int start, int end>
struct ForLoop_Compile
{
	static_assert(start <= end, "end must be greater than start");
	
	/// <summary>
	/// Just Loop Job
	/// </summary>
	/// <param name="job"></param>
	static void Loop(const std::function<void()>& job)
	{
		job();

		if constexpr (start < end)
		{
			ForLoop_Compile<start + 1, end>::Loop(job);
		}
	}

	/// <summary>
	/// For Use loop value(start ~ end).
	/// 
	/// Loop variable must be at first function argument
	/// And Never put reference to loop variable
	/// 
	/// You Can't change value of loop varaible at inside of loop function
	/// 
	/// 
	/// Example)
	/// 
	/// void addLoop(int loop, int initialValue)
	/// {
	/// 	initialValue += loop;
	/// }
	/// </summary>
	/// <typeparam name="F"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	/// <param name="f"></param>
	/// <param name="...args"></param>
	template <typename F, typename... Args, std::enable_if_t<std::is_function_v< std::remove_reference_t<F> >, bool> = true>
	static void Loop(F&& f, Args&&... args)
	{
		std::invoke(std::forward<F>(f), start, std::forward<Args>(args)...);

		if constexpr (start < end)
		{
			ForLoop_Compile<start + 1, end>::Loop(std::forward<F>(f), std::forward<Args>(args)...);
		}
	}
	
	
	
};
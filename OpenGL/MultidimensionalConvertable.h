#pragma once
//#include <iostream>
//#include <cstddef>
#include <concepts>
#include <type_traits>
//#include <type_traits>
//using namespace std::literals;

namespace Concepts
{
	template<typename Dividend, typename Divider>
	struct is_sizes_divided_completely
	{
		static constexpr bool value = sizeof(Dividend) % sizeof(Divider) == 0;
	};
	template<typename Dividend, typename Divider>
	auto is_sizes_divided_completely_v = is_sizes_divided_completely<Dividend, Divider>::value;

	template< typename ConvertionType, typename... Args>
	concept MultidimentionalConvertable = requires	{(is_sizes_divided_completely_v<Args, ConvertionType> && ...); };
	template< typename ConvertionType>
	concept Big = requires	{sizeof(ConvertionType)>3; };

	template<typename T, typename U>
	concept can_add = requires(T t, U u) { t + u; };
}
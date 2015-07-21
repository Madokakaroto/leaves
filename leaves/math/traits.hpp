#pragma once

#include <type_traits>
#include <type_list.hpp>
//#include "detail\promotion.hpp"

// anonymous namespace to avoid ADL issues
namespace
{
	template <typename T>
	T leaves_numeric_sqrt(T t)
	{
		return std::sqrt(t);
	}

	template <typename T>
	auto leaves_numeric_abs(T const& t)
		-> std::enable_if_t<!std::is_unsigned<T>::value, T>
	{
		return std::abs(t)
	}

	template <typename T>
	auto leaves_numeric_abs(T const& t)
		-> std::enable_if_t<std::is_unsigned<T>::value, T>
	{
		return t;
	}
}

namespace leaves { namespace math 
{
	template <typename T, typename P>
	struct promotion_traits
	{
		typedef typename std::common_type<T, P>::type type;
	};

	template <typename T, typename P>
	using promotion_traits_t = typename promotion_traits<T, P>::type;

	template <typename T>
	struct type_traits;

	template <typename ... Args>
	struct is_same;

	template <typename T>
	struct is_same<T>
	{
		static const bool value = true;
		typedef T type;
	};

	template <typename T1, typename T2>
	struct is_same<T1, T2> : std::is_same<T1, T2>
	{
		typedef std::enable_if_t<value, T1> type;
	};

	template <typename T1, typename T2, typename ... Args>
	struct is_same<T1, T2, Args...>
	{
		static const bool value = is_same<T1, T2>::value && is_same<T2, Args...>::value;
		typedef std::enable_if_t<value, T1> type;
	};

	template <typename T>
	struct is_scalar
	{
	private:
		static const bool is_const = std::is_const<T>::value;
		static const bool is_signed = std::is_signed<T>::value;
		static const bool is_arithmetic = std::is_arithmetic<T>::value;
		static const bool is_reference = std::is_reference<T>::value;
	public:
		static const bool value = is_signed && is_arithmetic && !is_const && !is_reference;
	};

	template <typename T>
	struct is_place_holder : std::false_type
	{
	};
} }
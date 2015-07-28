#pragma once

#include <type_traits>
#include <leaves\type_list.hpp>
//#include "detail\promotion.hpp"

// anonymous namespace to avoid ADL issues
namespace
{
	template <typename T>
	T leaves_numeric_inverse(T t)
	{
		return T{1} / t;
	}

	template <typename T>
	T leaves_numeric_square(T t)
	{
		return t * t;
	}

	template <typename T>
	T leaves_numeric_sqrt(T t)
	{
		return std::sqrt(t);
	}

	template <typename T>
	T leaves_numeric_abs(T t)
	{
		return std::abs(t);
	}

	template <typename T>
	T leaves_numeric_positive(T t)
	{
		return t;
	}
}

namespace leaves { namespace math 
{
	// size type 
	typedef std::size_t size_type;

	// type promotion
	template <typename T, typename P>
	struct promotion_traits
	{
		typedef typename std::common_type<T, P>::type type;
	};

	template <typename T, typename P>
	using promotion_traits_t = typename promotion_traits<T, P>::type;

	template <typename T>
	struct type_traits;

	// is all types the same type
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

	// is scalar
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

	// is scalar expression
	template <typename E>
	struct is_scalar_expression : std::is_base_of<scalar_expression<E>, E>
	{
	};

	// is vector
	template <typename T>
	struct is_vector : std::false_type
	{
	};

	template <typename T, size_type N, typename B>
	struct is_vector<vector<T, N, B> > : std::true_type
	{
	};

	// is vector expression
	namespace detail
	{
		template <typename E>
		struct is_vector_expression_impl : std::is_base_of<vector_expression<E>, E>
		{
		};
	}

	template <typename E>
	struct is_vector_expression : detail::is_vector_expression_impl<
		std::remove_const_t<std::remove_const_t<E> > >
	{
	};

	// is matrix
	template <typename T>
	struct is_matrix : std::false_type
	{
	};

	// is matrix expression
	template <typename E>
	struct is_matrix_expression : std::is_base_of<matrix_expression<E>, E>
	{
	};

	// arguments get helper
	template <size_t Index>
	struct argument
	{
		template <typename Arg0, typename ... Args>
		static auto get(Arg0 arg0, Args ... args)
			-> decltype(argument<Index - 1>::get(args...))
		{
			return argument<Index - 1>::get(args...);
		}
	};

	template <>
	struct argument<0>
	{
		template <typename Arg0, typename ... Args>
		static Arg0 get(Arg0 arg0, Args ... args)
		{
			return arg0;
		}
	};

	// arguments count
	template <typename ... Args>
	struct argument_count
	{
		static size_type const value = sizeof...(Args);
	};

	// bigger than
	template <typename T, T M, T N>
	struct bigger_than
	{
		static bool const value = M > N;
	};

	// equal to
	template <typename T, T M, T N>
	struct equal
	{
		static bool const value = M == N;
	};

	namespace detail
	{
		template <typename T, T X0, T... Xs>
		struct max_impl
		{
			typedef T type;
			static type const recursive_max = max_impl<T, Xs>::value;
			static type const value = X0 > recursive_max ? X0 : recursive_max;
		};

		template <typename T, T X0>
		struct max<T, X0>
		{
			typedef T type;
			static type const value = X0;
		};
	}

	template <typename T, T ... Xs>
	struct max : detail::max_impl<T, Xs...>
	{
	};
} }

// expression traits
//namespace leaves { namespace math
//{
//	template <typename E>
//	struct expression_tratis_impl;
//
//	template <typename E>
//	struct expression_traits : expression_tratis_impl<std::remove_reference_t<E>>
//	{
//	};
//
//	template <typename E>
//	struct expression_tratis_impl<template_expression<E>>
//	{	
//	};
//
//	template <typename E>
//	struct expression_tratis_impl<vector_expression<E>>
//	{
//	};
//
//	template <typename E, typename F>
//	struct expression_tratis_impl<vector_unary<E, F>>
//	{
//	};
//} }
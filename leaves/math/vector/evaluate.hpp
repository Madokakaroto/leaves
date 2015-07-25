#pragma once 

#include "detail\evaluate_detail.hpp"

namespace leaves { namespace math 
{
	// evalute when assign
	template
	<
		template <typename, typename> class ScalarBinary,
		typename E1, typename E2
	>
	void assign(vector_expression<E1>& e1, vector_expression<E2> const& e2)
	{
		typedef E1 left_expression_type;
		typedef E2 right_expression_type;
		static_assert(!std::is_const<left_expression_type>::value, "l-value connot be const!");
		typedef typename left_expression_type::value_type left_value_type;
		typedef typename right_expression_type::value_type right_value_type;
		typedef ScalarBinary<left_value_type, right_value_type> function_type;

		typedef vector_detail::vector_assign_vector<
			function_type, left_expression_type, right_expression_type> assign_type;

		assign_type::apply(get_expression(e1), get_expression(e2));
	}

	template 
	<
		template <typename, typename> class ScalarBinary,
		typename E, typename T
	>
	auto assign(vector_expression<E>& e, T scalar)
		-> std::enable_if_t<is_scalar<T>::value>
	{
		typedef E expression_type;
		typedef T scalar_type;
		typedef typename expression_type::value_type value_type;
		typedef ScalarBinary<value_type, scalar_type> function_type;

		typedef vector_detail::vector_assign_scalar<
			function_type, expression_type, scalar_type> assign_type;

		assign_type::apply(get_expression(e), scalar);
	}

	template 
	<
		template <typename, typename> class ScalarBinary,
		typename E, typename ... Args
	>
	auto assign(vector_expression<E>& e, Args ... args)
		-> std::enable_if_t<bigger_than<size_type, argument_count<Args...>::value, 1>::value>
	{
		typedef E expression_type;
		static_assert(!std::is_const<E>::value, "l-value connot be const!");
		typedef typename expression_type::value_type value_type;
		typedef typename is_same<Args...>::type scalar_type;
		static_assert(is_scalar<scalar_type>::value, "Scalar type only!");
		typedef ScalarBinary<value_type, scalar_type> function_type;

		typedef vector_detail::vector_assign_scalar_variadic<
			function_type, expression_type, Args...> assign_type;

		assign_type::apply(get_expression(e), args...);
	}

	// evalute when reduce
	template
	<
		template <typename, typename> class ScalarBinary,
		typename E
	>
	auto reduce(vector_expression<E> const& e)
		-> typename vector_detail::vector_reduce_scalar<E, ScalarBinary>::return_type
	{
		typedef vector_detail::vector_reduce_scalar<E, ScalarBinary> reduce_type;
		return reduce_type::apply(get_expression(e));
	}

	template 
	<
		template <typename> class ScalarUnary,
		template <typename, typename> class ScalarBinary,
		typename E
	>
	auto reduce(vector_expression<E> const& e)
		-> typename vector_detail::vector_reduce_scalar_ex<E, ScalarUnary, ScalarBinary>::return_type
	{
		typedef vector_detail::vector_reduce_scalar_ex<E, ScalarUnary, ScalarBinary> reduce_type;
		return reduce_type::apply(get_expression(e));
	}

	template
	<
		template <typename, typename> class ScalarBinary1,
		template <typename, typename> class ScalarBinary2,
		typename E1, typename E2
	>
	auto reduce(vector_expression<E1> const& e1, vector_expression<E2> const& e2)
	-> typename vector_detail::vector_binary_reduce_scalar<E1, E2, ScalarBinary1, ScalarBinary2>::return_type
	{
		typedef vector_detail::vector_binary_reduce_scalar<E1, E2, ScalarBinary1, ScalarBinary2> reduce_type;
		return reduce_type::apply(e1, e2);
	}

} }
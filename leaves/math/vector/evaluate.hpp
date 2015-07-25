#pragma once 

#include "detail\evaluate_detail.hpp"

namespace leaves { namespace math 
{
	template
	<
		template <typename, typename> class ScalarBinary,
		typename E1, typename E2
	>
	void evaluate(vector_expression<E1>& e1, vector_expression<E2> const& e2)
	{
		typedef E1 left_expression_type;
		typedef E2 right_expression_type;
		static_assert(!std::is_const<left_expression_type>::value, "l-value connot be const!");
		typedef typename left_expression_type::value_type left_value_type;
		typedef typename right_expression_type::value_type right_value_type;
		typedef ScalarBinary<left_value_type, right_value_type> function_type;

		typedef vector_detail::evaluate_vector_with_vector<
			function_type, left_expression_type, right_expression_type> evaluate_type;

		evaluate_type::apply(get_expression(e1), get_expression(e2));
	}

	template 
	<
		template <typename, typename> class ScalarBinary,
		typename E, typename T
	>
	auto evaluate(vector_expression<E>& e, T scalar)
		-> std::enable_if_t<is_scalar<T>::value>
	{
		typedef E expression_type;
		typedef T scalar_type;
		typedef typename expression_type::value_type value_type;
		typedef ScalarBinary<value_type, scalar_type> function_type;

		typedef vector_detail::evaluate_vector_with_scalar<
			function_type, expression_type, scalar_type> evaluate_type;

		evaluate_type::apply(get_expression(e), scalar);
	}

	template 
	<
		template <typename, typename> class ScalarBinary,
		typename E, typename ... Args
	>
	auto evaluate(vector_expression<E>& e, Args ... args)
		-> std::enable_if_t<bigger_than<size_type, argument_count<Args...>::value, 1>::value>
	{
		typedef E expression_type;
		static_assert(!std::is_const<E>::value, "l-value connot be const!");
		typedef typename expression_type::value_type value_type;
		typedef typename is_same<Args...>::type scalar_type;
		static_assert(is_scalar<scalar_type>::value, "Scalar type only!");
		typedef ScalarBinary<value_type, scalar_type> function_type;

		typedef vector_detail::evaluate_vector_with_scalar_variadic<
			function_type, expression_type, Args...> evaluate_type;

		evaluate_type::apply(get_expression(e), args...);
	}

	template
	<
		template <typename, typename> class ScalarBinary,
		typename E
	>
	auto evaluate(vector_expression<E> const& e, typename E::value_type init)
		-> typename E::value_type
	{
		typedef E expression_type;
		typedef typename expression_type::value_type value_type;
		typedef ScalarBinary<value_type, value_type> function_type;

		typedef vector_detail::evaluate_vector_to_scalar<
			function_type, expression_type> evaluate_type;
		
		return evaluate_type::apply(get_expression(e), init);
	}
} }
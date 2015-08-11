#pragma once 

namespace leaves { namespace math 
{
	template 
	<
		template <typename, typename> class FP,		// FP is short for function policy
		typename E1, typename E2
	>
	void assign(vector_expression<E1>& e1, vector_expression<E2> const& e2)
	{
		typedef FP<E1, E2> function_type;
		function_type::apply(get_expression(e1), get_expression(e2));
	}

	template 
	<
		template <typename, typename> class FP,
		typename E, typename T
	>
	auto assign(vector_expression<E>& e, T t)
		-> std::enable_if_t<is_scalar<T>::value>
	{
		typedef FP<E, T> function_type;
		function_type::apply(get_expression(e), t);
	}

	template 
	<
		template <typename, typename...> class FP,
		typename E, typename ... Args
	>
	auto assign(vector_expression<E>& e, Args ... args)
		-> std::enable_if_t<bigger_than<size_type, argument_count<Args...>::value, 1>::value>
	{
		typedef FP<E, Args...> function_type;
		function_type::apply(get_expression(e), args...);
	}

} }
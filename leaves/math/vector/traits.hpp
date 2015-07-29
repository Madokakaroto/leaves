#pragma once

namespace leaves { namespace math
{
	template
	<
		typename E,
		template <typename> class UP		// UP is short for unary policy
	>
	struct vector_unary_traits
	{
	private:
		typedef std::add_const_t<E> unary_expression;
		typedef UP<unary_expression> function_type;
	public:
		typedef vector_unary<unary_expression, function_type> type;
	};

	template
	<
		typename E1, typename E2, 
		template <typename, typename> class BP  // BP is short for binary policy
	>
	struct vector_binary_traits
	{
	private:
		typedef std::add_const_t<E1> expression_type1;
		typedef std::add_const_t<E2> expression_type2;
		typedef BP<expression_type1, expression_type2> function_type;
	public:
		typedef vector_binary<expression_type1, expression_type2, function_type> type;
	};

	template 
	<
		typename E, typename T,
		template <typename, typename> class BP
	>
	struct vector_scalar_traits
	{
	private:
		typedef std::add_const_t<E> expression_type;
		typedef BP<expression_type, T> function_type;
	public:
		typedef vector_scalar<expression_type, T, function_type> type;
	};

	template 
	<
		typename E, 
		template <typename> class UP
	>
	struct vector_to_scalar_traits
	{
	private:
		typedef std::add_const_t<E> expression_type;
		typedef UP<expression_type> function_type;
	public:
		typedef vector_to_scalar<expression_type, function_type> type;
		typedef typename function_type::value_type return_type;
	};
} }
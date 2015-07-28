#pragma once

namespace leaves { namespace math 
{
	template <typename E, template <typename> class ScalarUnary>
	struct vector_unary_traits
	{
	private:
		typedef vector_unary<std::add_const_t<E>, ScalarUnary> expression_type;
	public:
		typedef expression_type result;
	};

	template
	<
		typename E1, typename E2,
		template <typename, typename> class ScalarBinary
	>
	struct vector_binary_traits
	{
	private:
		typedef std::add_const_t<E1> left_expression_type;
		typedef std::add_const_t<E2> right_expression_type;
		typedef vector_binary<left_expression_type, right_expression_type, ScalarBinary> expression_type;
	public:
		typedef expression_type result;
	};

	template 
	<
		typename E, typename T,
		template <typename, typename> class ScalarBinary
	>
	struct vector_scalar_traits
	{
	private:
		typedef std::add_const_t<E> sub_expresion_type;
		typedef vector_scalar<sub_expresion_type, T, ScalarBinary> expression_type;
	public:
		typedef expression_type result;
	};

} }
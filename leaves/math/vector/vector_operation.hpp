#pragma once

namespace leaves { namespace math
{
	template 
	<
		typename ExprT, 
		template <typename T> class ScalarUnary
	>
	class vector_unary : 
		public vector_expression<vector_unary<ExprT, ScalarUnary> >
	{
		typedef vector_unary<ExprT, ScalarUnary> this_type;
	public:
		typedef ExprT expression_type;
		typedef typename expression_type::value_type value_type;
		typedef typename expression_type::const_reference const_reference;
		typedef const_reference reference;
		typedef typename expression_type::base_tag  base_tag;
		typedef ScalarUnary<value_type> function_type;
		static const size_type size = expression_type::size;

	public:

		explicit vector_unary(expression_type& expression)
			: expression_(expression)
		{

		}

		const_reference operator() (size_type index) const
		{
			return function_type::apply(expression_(index));
		}

		template <size_type Index>
		const_reference get() const
		{
			return function_type::apply(expression_.get<Index>());
		}

		using vector_expression<this_type>::operator();

	private:

		expression_type& expression_;
	};

	template <typename ExprT, template <typename T> class ScalarUnary>
	struct vector_unary_traits
	{
	private:
		typedef vector_unary<std::add_const_t<ExprT>, ScalarUnary> expression_type;
	public:
		typedef expression_type result;
	};

	template <typename ExprT>
	auto operator - (vector_expression<ExprT> const& e)
		-> typename vector_unary_traits<ExprT, scalar_negative>::result
	{
		typedef typename vector_unary_traits<ExprT, scalar_negative>::result expression_type;
		return expression_type{ get_expression(e) };
	}

	template 
	<
		typename ExprLeftT, 
		typename ExprRightT,
		template <typename T1, typename T2> class ScalarBinary
	>
	class vector_binary : public vector_expression<vector_binary<ExprLeftT, ExprRightT, ScalarBinary> >
	{
		typedef vector_binary<ExprLeftT, ExprRightT, ScalarBinary> this_type;
		template <size_type S1, size_type S2>
		struct same_size { };
		template <size_type S1>
		struct same_size<S1, S1> { static const size_type value = S1; };
	public:
		typedef ExprLeftT l_expression_type;
		typedef ExprRightT r_expression_type;
		typedef typename l_expression_type::value_type l_value_type;
		typedef typename r_expression_type::value_type r_value_type;
		typedef ScalarBinary<l_value_type, r_value_type> function_type;
		typedef typename function_type::return_type value_type;
		typedef value_type const_reference;
		typedef const_reference reference;
		
		typedef std::enable_if_t <
			std::is_same<
				typename l_expression_type::base_tag,
				typename r_expression_type::base_tag>::value,
			typename l_expression_type::base_tag > base_tag;

		static const size_type size = same_size<l_expression_type::size, r_expression_type::size>::value;
	public:

		vector_binary(l_expression_type& left, r_expression_type& right)
			: left_(left)
			, right_(right)
		{

		}

		const_reference operator() (size_type index) const
		{
			return function_type::apply(left_(index), right_(index));
		}

		template <size_type Index>
		const_reference get() const
		{
			return function_type::apply(left_.get<Index>(), right_.get<Index>());
		}

		using vector_expression<this_type>::operator();

	private:
		l_expression_type& left_;
		r_expression_type& right_;
	};

	template
	<
		typename ExprLeftT,
		typename ExprRightT,
		template <typename T1, typename T2> class ScalarBinary
	>
	struct vector_binary_traits
	{
	private:
		typedef std::add_const_t<ExprLeftT> l_expression_type;
		typedef std::add_const_t<ExprRightT> r_expression_type;
		typedef vector_binary<l_expression_type, r_expression_type, ScalarBinary> expression_type;
	public:
		typedef expression_type result;
	};

	template <typename ExprLeftT, typename ExprRightT>
	auto operator + (template_expression<ExprLeftT> const& lhs, template_expression<ExprRightT> const& rhs)
		-> typename vector_binary_traits<ExprLeftT, ExprRightT, scalar_add>::result
	{
		typedef typename vector_binary_traits<ExprLeftT, ExprRightT, scalar_add>::result expression_type;
		return expression_type{ get_expression(lhs), get_expression(rhs) };
	}

	template <typename ExprLeftT, typename ExprRightT>
	auto operator - (template_expression<ExprLeftT> const& lhs, template_expression<ExprRightT> const& rhs)
		-> typename vector_binary_traits<ExprLeftT, ExprRightT, scalar_sub>::result
	{
		typedef typename vector_binary_traits<ExprLeftT, ExprRightT, scalar_sub>::result expression_type;
		return expression_type{ get_expression(lhs), get_expression(rhs) };
	}

	template <typename ExprLeftT, typename ExprRightT>
	auto operator * (template_expression<ExprLeftT> const& lhs, template_expression<ExprRightT> const& rhs)
		-> typename vector_binary_traits<ExprLeftT, ExprRightT, scalar_mult>::result
	{
		typedef typename vector_binary_traits<ExprLeftT, ExprRightT, scalar_mult>::result expression_type;
		return expression_type{ get_expression(lhs), get_expression(rhs) };
	}

	template <typename ExprLeftT, typename ExprRightT>
	auto operator / (template_expression<ExprLeftT> const& lhs, template_expression<ExprRightT> const& rhs)
		-> typename vector_binary_traits<ExprLeftT, ExprRightT, scalar_div>::result
	{
		typedef typename vector_binary_traits<ExprLeftT, ExprRightT, scalar_div>::result expression_type;
		return expression_type{ get_expression(lhs), get_expression(rhs) };
	}
} }
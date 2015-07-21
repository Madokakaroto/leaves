#pragma once

namespace leaves { namespace math
{
	template <size_t Size, typename ... Args>
	struct check_ctor_param
	{
	private:
		typedef is_same<Args...> same_type_check;
	public:
		static const bool value = same_type_check::value && Size == sizeof...(Args);
		typedef std::enable_if_t<value, typename same_type_check::type> type;
	};

	template <typename PL, typename ... PLs>
	struct check_place_hodler_param
	{
		static const bool value = is_place_holder<PL>::value && check_place_hodler_param<PLs...>::value;
	};

	template <typename ExprT>
	struct is_vector : std::false_type
	{
	};

	template <typename ScalarT, std::size_t Size, typename BaseT>
	struct is_vector<vector<ScalarT, Size, BaseT> > : std::true_type
	{
	};

	template <typename ExprT>
	struct is_vector_expression : std::is_base_of<vector_expression<ExprT>, ExprT>
	{
	};

	template <typename PL>
	struct is_vector_place_hodler : std::false_type {};

	template <size_t I, typename ExprT>
	auto get(vector_expression<ExprT>& ve)
		-> typename ExprT::reference
	{
		typedef ExprT expression_type;

		return get_expression(ve).get<I>();
	}

	template <size_t I, typename ExprT>
	auto get(vector_expression<ExprT> const& ve)
		-> typename ExprT::const_reference
	{
		typedef ExprT expression_type;

		return get_expression(ve).get<I>();
	}
} }
#pragma once

namespace leaves { namespace math
{
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

} }
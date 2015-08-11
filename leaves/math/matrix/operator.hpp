#pragma once

namespace leaves { namespace math 
{
	template 
	<
		typename E1, typename E2,
		template <typename ,typename> class BP
	>
	void assign(matrix_expression<E1>& e1, matrix_expression<E2> const& e2)
	{
		typedef BP<E1, E2> function_type;
		function_type::apply(get_expression(e1), get_expression(e2));
	}
} }
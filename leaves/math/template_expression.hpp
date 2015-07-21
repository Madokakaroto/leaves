#pragma once

namespace leaves { namespace math
{
	template <typename ExprT>
	class template_expression
	{
	public:
		typedef ExprT expression_type;
	protected:
		template_expression() = default;
		~template_expression() = default;
	private:
		template_expression& operator= (template_expression const&) = delete;
	};

	template <typename ExprT>
	auto get_expression(template_expression<ExprT>& expression) -> ExprT&
	{
		return static_cast<ExprT&>(expression);
	}

	template <typename ExprT>
	auto get_expression(template_expression<ExprT> const& expression) ->ExprT const&
	{
		return static_cast<ExprT const&>(expression);
	}
} }
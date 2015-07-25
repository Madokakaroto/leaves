#pragma once

namespace leaves { namespace math
{
	template <typename E>
	class template_expression
	{
	public:
		typedef E expression_type;
	protected:
		template_expression() = default;
		~template_expression() = default;
	private:
		template_expression& operator= (template_expression const&) = delete;
	};

	template <typename E>
	auto get_expression(template_expression<E>& expression) -> E&
	{
		return static_cast<E&>(expression);
	}

	template <typename E>
	auto get_expression(template_expression<E> const& expression) ->E const&
	{
		return static_cast<E const&>(expression);
	}
} }
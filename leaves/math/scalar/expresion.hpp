#pragma once

namespace leaves { namespace math
{
	// template parametres
	// Expr - a explicit expression
	template <typename Expr>
	class scalar_expression : public template_expression<Expr>
	{
	public:
		using expression_type = Expr;
		using type_tag = scalar_tag;
	};

	template <typename T>
	class scalar_reference : public template_expression<scalar_reference<T> >
	{
		typedef scalar_reference<T> this_type;
	public:
		static_assert(is_scalar<T>::value, "Must be scalar type!");
		typedef T value_type;
		typedef std::conditional_t<
			std::is_const<T>::value,
			value_type,
			value_type&> reference;

		explicit scalar_reference(reference ref)
			: ref_(ref)
		{
		}

		operator value_type() const
		{
			return ref_;
		}

		reference operator() ()
		{
			return ref_;
		}

		value_type operator() () const
		{
			return ref_;
		}

	private:
		reference ref_;
	};
} }
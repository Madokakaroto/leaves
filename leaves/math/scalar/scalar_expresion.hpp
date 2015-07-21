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
		using type_category = scalar_tag;

		auto operator() () const -> expression_type const&
		{
			return *static_cast<const expression_type *>(this);
		}
		
		auto operator() () -> expression_type
		{
			return *static_cast<expression_type*>(this);
		}
	};

	template <typename T>
	class scalar_reference : public template_expression < scalar_reference<T> >
	{
		typedef scalar_reference self_type;
	public:
		using value_type = T;
		using const_reference = value_type const&;
		using reference = std::conditional_t <
			std::is_const<T>::value,
			const_reference,
			value_type& > ;

		using const_closure_type = self_type const;
		using closure_type = self_type;

		explicit scalar_reference(reference ref)
			: ref_(ref)
		{
		}

		operator value_type() const
		{
			return ref_;
		}

		self_type& operator= (self_type const& other)
		{
			ref_ = other.ref_;
			return *this;
		}

		// is this right ?????
		template <typename Expr>
		self_type& operator= (scalar_expression<Expr> const& other)
		{
			ref_ = other;
			return *this;
		}

		bool same_clousre(self_type const& other)
		{
			return &ref_ == &other.ref_;
		}

	private:
		reference ref_;
	};

	template <typename T>
	class scalar_value : public scalar_expression<scalar_value<T> >
	{
		using self_type = scalar_value;
	public:
		using value_type = T;
		using const_reference = value_type const&;
		using reference = std::conditional_t <
			std::is_const<T>::value,
			const_reference,
			value_type& >;

		using const_clousre_type = scalar_reference<const self_type> const;
		using clousre_type = scalar_reference<self_type>;
		
		explicit scalar_value(value_type value)
			: value_(value)
		{
		}

		operator value_type() const
		{
			return value_;
		}

		self_type& operator= (self_type const& other)
		{
			value_ = other.value_;
			return *this;
		}

		template <typename Expr>
		self_type& operator= (scalar_expression<Expr> const& other)
		{
			value_ = other;
			return *this;
		}

		bool same_closure(self_type const& other) const
		{
			return this == &other;
		}

	private:
		value_type value_;
	};
} }
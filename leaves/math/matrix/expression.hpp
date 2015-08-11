#pragma once

namespace leaves { namespace math
{
	template <typename E>
	class matrix_expression : public template_expression<matrix_expression<E>>
	{
	public:
		typedef E expression_type;
		typedef matrix_tag type_tag;
	};

	template <typename E, typename P>
	class matrix_row_proxy : public vector_expression<matrix_row_proxy<E, P>>
	{
		typedef matrix_row_proxy<E, P> this_type;
	public:
		static_assert(is_matrix_row<P>::value, "Must be a matrix row type!");
		static_assert(E::complexity() <= 4, "Too complex to calculate!");
		typedef E expression_type;
		typedef P place_holder;
		typedef typename expression_type::value_type value_type;
		typedef std::conditional_t<std::is_const<E>::value,
			typename expression_type::reference,
			typename expression_type::const_reference> reference;
		typedef typename expression_type::const_reference const_reference;
		typedef typename expression_type::major_order major_order;

		static constexpr size_type complexity()
		{
			return expression_type::complexity();
		}

		static constexpr size_type size()
		{
			return expression_type::col_size();
		}

	public:
		explicit matrix_row_proxy(expression_type& e)
			: e_(e)
		{

		}

		value_type& operator() (size_type index)
		{
			static_assert(!std::is_const<expression_type>::value, "Cannot conver from a lvalue to rvalue!");
			static_assert(complexity() <= 1, "Too complex to calculate!");
			return e_(place_holder::row(), index);
		}

		value_type operator() (size_type index)
		{
			static_assert(complexity() <= 1, "Too complex to calculate!");
			return e_(place_holder::row(), index);
		}

		template <size_type Index>
		value_type& get()
		{
			return operator()(Index);
		}

		template <size_type Index>
		value_type get() const
		{
			return operator()(Index);
		}

		typedef vector<value_type, size(), major_to_base_t<major_order>> row_vector_type;

		row_vector_type& get()
		{

		}

	private:
		matrix_row_proxy e_;
	};
} }
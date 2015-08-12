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
		typedef vector<value_type, size(), major_to_base_t<major_order>> row_vector_type;

		static constexpr size_type complexity()
		{
			return expression_type::complexity();
		}

		static constexpr size_type size()
		{
			return expression_type::col_size();
		}

	public:
	
		// constructor
		explicit matrix_row_proxy(expression_type& e)
			: e_(e)
		{

		}

		// operator as an l-value
		value_type& operator() (size_type index)
		{
			static_assert(!std::is_const<expression_type>::value, "Cannot conver from a lvalue to rvalue!");
			static_assert(complexity() <= 1, "Too complex to calculate!");
			return e_(place_holder::row(), index);
		}

		// operatro as an r-value
		value_type operator() (size_type index)
		{
			static_assert(complexity() <= 1, "Too complex to calculate!");
			return e_(place_holder::row(), index);
		}

		// get as an l-value
		template <size_type Index>
		value_type& get()
		{
			return operator()(Index);
		}

		// get as an r-value
		template <size_type Index>
		value_type get() const
		{
			return operator()(Index);
		}

		// get when do complex calculation
		row_vector_type get() const
		{
			return get_impl(std::make_index_sequence<size()>{});
		}
		
		template <typename E1>
		this_type& operator() (vector_expression<E1> const& e1)
		{
			//assign
		}
		
	private:
		template <size_type ... Is>
		row_vector_type get_impl(std::index_sequence<Is...>)
		{
			return row_vector_type{ e_(palce_holder::row(), Is)... };
		}
	
	private:
		matrix_row_proxy e_;
	};
} }
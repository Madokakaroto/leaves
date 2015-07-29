#pragma once

namespace leaves { namespace math 
{
	template <typename E>
	class vector_expression : public template_expression<E>
	{
	public:
		typedef E expression_type;
		typedef std::add_const_t<E> const_expression_type;
		typedef vector_tag type_tag;

		// PL is short for palce hodler
		template <typename ... PLs>
		auto operator() (PLs ... pls)
			-> std::enable_if_t<
				check_vector_place_hodlers<PLs...>::value, 
				vector_proxy<expression_type, vector_indexor<PLs...> > >
		{
			typedef vector_proxy<expression_type, vector_indexor<PLs...> > vector_proxy_type;
			return vector_proxy_type{ get_expression(*this) };
		}

		template <typename ... PLs>
		auto operator() (PLs ... pls) const
			-> std::enable_if_t<
				check_vector_place_hodlers<PLs...>::value, 
				vector_proxy<const_expression_type, vector_indexor<PLs...> > >
		{
			typedef vector_proxy<const_expression_type, vector_indexor<PLs...> > vector_proxy_type;
			return vector_proxy_type{ get_expression(*this) };
		}
	};

	// I is short for indexor
	template <typename E, typename I>
	class vector_proxy
		: public vector_expression<vector_proxy<E, I> >
	{
		typedef vector_proxy<E, I> this_type;
	public:
		typedef E expression_type;
		typedef typename expression_type::value_type value_type;
		typedef std::conditional_t<
			std::is_const<expression_type>::value,
			typename expression_type::value_type,
			typename expression_type::reference> reference;
		typedef typename expression_type::base_tag base_tag;
		typedef I indexor_type;
		static size_type const size = indexor_type::size;
		static size_type const complexity = expression_type::complexity;

		explicit vector_proxy(expression_type& e)
			: e_(e)
		{
		}

		template <size_type Index>
		reference get()
		{
			static_assert(Index < size, "vector_proxy::get");
			return e_(indexor_type::template get<Index>::value);
		}

		template <size_type Index>
		value_type get() const
		{
			static_assert(Index < size, "vector_proxy::get");
			return e_.get<indexor_type::template get<Index>::value>();
		}

		using vector_expression<this_type>::operator();

	private:
		expression_type& e_;
	};

	// policy based design
	template <typename E, typename F>
	class vector_unary : 
		public vector_expression<vector_unary<E, F>>
	{
		typedef vector_unary<E, F> this_type;
	public:			
		typedef E expression_type;
		typedef F function_type;	
		typedef typename function_type::value_type value_type;			
		typedef value_type reference;									
		typedef typename function_type::base_tag base_tag;
		static size_type const size = function_type::size;
		static size_type const complexity = function_type::complexity;	
	public:
		explicit vector_unary(expression_type& e)
			: e_(e)
		{
		}
	
		value_type operator() (size_type index) const
		{
			return function_type::apply(e_, index);
		}
	
		template <size_type Index>
		value_type get() const
		{
			return function_type::apply<Index>(e_);
		}
	
		using vector_expression<this_type>::operator();
	
	private:
		expression_type& e_;
	};

	template <typename E1, typename E2, typename F>
	class vector_binary : 
		public vector_expression<vector_binary<E1, E2, F>>
	{
		typedef vector_binary<E1, E2, F> this_type;
	public:
		typedef E1 expression_type1;
		typedef E2 expression_type2;
		typedef F function_type;
		typedef typename function_type::value_type value_type;
		typedef value_type reference;
		typedef typename function_type::base_tag base_tag;
		static size_type const size = function_type::size;
		static size_type const complexity = function_type::complexity;
	public:
		vector_binary(expression_type1& l, expression_type2& r)
			: e1_(l)
			, e2_(r)
		{
		}

		value_type operator() (size_type i) const
		{
			return function_type::apply(e1_, e2_, i);
		}

		template <size_type I>
		value_type get() const
		{
			return function_type::apply<I>(e1_, e2_);
		}

		using vector_expression<this_type>::operator();

	private:
		expression_type1&	e1_;
		expression_type2&	e2_;
	};

	template <typename E, typename T, typename F>
	class vector_scalar :
		public vector_expression<vector_scalar<E, T, F>>
	{
		typedef vector_scalar<E, T, F> this_type;
	public:
		typedef E expression_type;
		typedef T scalar_type;
		typedef F function_type;
		typedef typename function_type::value_type value_type;
		typedef typename function_type::reference reference;
		typedef typename function_type::base_tag base_tag;
		static size_type const size = function_type::size;
		static size_type const complexity = function_type::complexity;
	public:
		vector_scalar(expression_type& e, scalar_type v)
			: e_(e)
			, v_(v)
		{
		}

		value_type operator() (size_type i) const
		{
			return function_type::apply(e_, v_, i)
		}

		template <size_type I>
		value_type get() const
		{
			return function_type::apply<I>(e_, v_);
		}

		using vector_expression<this_type>::operator();

	private:
		expression_type&	e_;
		scalar_type			v_;
	};

	template<typename E, typename F>
	class vector_to_scalar :
		public scalar_expression<vector_to_scalar<E, F>>
	{
		typedef vector_to_scalar<E, F> this_type;
	public:
		typedef E expression_type;
		typedef F function_type;
		typedef typename function_type::return_type value_type;
		typedef value_type reference;
	public:

		explicit vector_to_scalar(expression_type& e)
			: e_(e)
		{
		}

		operator value_type() const
		{
			return 0;
		}

		value_type operator() (void) const
		{
			return 0;
		}

	private:
		expression_type& e_;
	};
} }
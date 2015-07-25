#pragma once

namespace leaves { namespace math 
{
	template <typename E>
	class vector_expression : public template_expression<E>
	{
	public:
		typedef E expression_type;
		typedef std::add_const_t<E> const_expression_type;

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
		static const size_type size = indexor_type::size;

		explicit vector_proxy(expression_type& v)
			: e_(v)
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
	template
	< 
		typename E, 
		template <typename> class ScalarUnary
	>
	class vector_unary : 
		public vector_expression<vector_unary<E, ScalarUnary> >
	{
		typedef vector_unary<E, ScalarUnary> this_type;
	public:
		typedef E expression_type;
		typedef typename expression_type::value_type value_type;
		typedef typename value_type reference;
		typedef typename expression_type::base_tag base_tag;
		typedef ScalarUnary<value_type> function_type;
		static const size_type size = expression_type::size;
	
	public:
	
		explicit vector_unary(expression_type& e)
			: e_(e)
		{
		}
	
		value_type operator() (size_type index) const
		{
			return function_type::apply(e_(index));
		}
	
		template <size_type Index>
		value_type get() const
		{
			return function_type::apply(e_.get<Index>());
		}
	
		using vector_expression<this_type>::operator();
	
	private:
	
		expression_type& e_;
	};

	template
	<
		typename E1, typename E2,
		template <typename, typename> class ScalarBinary
	>
	class vector_binary : 
		public vector_expression<vector_binary<E1, E2, ScalarBinary> >
	{
		typedef vector_binary<E1, E2, ScalarBinary> this_type;
	public:
		typedef E1 left_expression_type;
		typedef E2 right_expression_type;
		typedef typename left_expression_type::value_type left_value_type;
		typedef typename right_expression_type::value_type right_value_type;
		static size_type const left_size = left_expression_type::size;
		static size_type const right_size = right_expression_type::size;
		static_assert(equal<size_type, left_size, right_size>::value, "Must have the same size!");
		typedef typename left_expression_type::base_tag left_base_tag;
		typedef typename right_expression_type::base_tag right_base_tag;
		static_assert(std::is_same<left_base_tag, right_base_tag>::value, "Must have the same tag");

		typedef ScalarBinary<left_value_type, right_value_type> function_type;
		typedef typename function_type::return_type value_type;
		typedef value_type reference;
		static size_type const size = left_size;
		typedef left_base_tag base_tag;
	
	public:
		
		vector_binary(left_expression_type& l, right_expression_type& r)
			: l_(l)
			, r_(r)
		{
		}

		value_type operator() (size_type index) const
		{
			return function_type::apply(l_(index), r_(index));
		}

		template <size_type I>
		value_type get() const
		{
			return function_type::apply(l_.get<I>(), r_.get<I>());
		}

		using vector_expression<this_type>::operator();

	private:

		left_expression_type&	l_;
		right_expression_type&	r_;
	};

	template 
	<
		typename E, typename T,
		template <typename, typename> class ScalarBinary
	>
	class vector_scalar :
		public vector_expression<vector_scalar<E, T, ScalarBinary> >
	{
		typedef vector_scalar<E, T, ScalarBinary> this_type;
	public:
		typedef E expression_type;
		typedef typename expression_type::value_type left_value_type;
		static_assert(is_scalar<T>::value, "Cannot be types except scalar!");
		typedef T scalar_type;
		typedef ScalarBinary<left_value_type, scalar_type> function_type;
		typedef typename function_type::return_type value_type;
		typedef value_type reference;
		static size_type const size = expression_type::size;
		typedef typename expression_type::base_tag base_type;

	public:

		vector_scalar(expression_type& e, scalar_type v)
			: e_(e)
			, v_(v)
		{
		}

		value_type operator() (size_type index) const
		{
			return function_type::apply(e_(index), v_);
		}

		template <size_type I>
		value_type get() const
		{
			return function_type::apply(e_.get<I>(), v_);
		}

		using vector_expression<this_type>::operator();

	private:

		expression_type&	e_;
		scalar_type			v_;
	};

	//template 
	//<
	//	typename T, typename E,
	//	template <typename, typename> class ScalarBinary
	//>
	//class scalar_vector :
	//	public vector_expression<scalar_vector<T, E, ScalarBinary> >
	//{
	//	typedef scalar_vector<T, E, ScalarBinary> this_type;
	//public:
	//	static_assert(is_scalar<T>::value, "Cannot be types except scalar!");
	//	typedef T scalar_type;
	//	typedef E expression_type;
	//	typedef typename expression_type::value_type right_value_type;
	//	typedef ScalarBinary<scalar_type, right_value_type> function_type;
	//	typedef typename function_type::return_type value_type;
	//	static size_type const size = expression_type::size;
	//	typedef typename function_type::base_tag base_tag;
	//
	//public:
	//
	//	scalar_vector(scalar_type v, expression_type& e)
	//		: v_(v)
	//		, e_(e)
	//	{
	//	}
	//
	//	value_type operator() (size_type index) const
	//	{
	//		return function_type::apply(e_(index), v_);
	//	}
	//
	//	template <size_type I>
	//	value_type get() const
	//	{
	//		return function_type::apply(e_.get<I>(), v_);
	//	}
	//
	//	using vector_expression<this_type>::operator();
	//
	//private:
	//	scalar_type			v_;
	//	expression_type&	e_;
	//};
} }
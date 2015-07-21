#pragma once

namespace leaves { namespace math
{
	template <typename ExprT>
	class vector_expression : public template_expression < ExprT >
	{
	public:
		typedef ExprT expression_type;
		typedef vector_tag type_category;

	private:

		template <typename IndexorT>
		using vector_proxy_p = vector_proxy < expression_type, IndexorT > ;

		template <typename IndexorT>
		using vector_proxy_cp = vector_proxy < expression_type const, IndexorT > ;

	public:

		template <typename ... PLs>
		auto operator() (PLs ... pls)
			->vector_proxy_p <indexor<PLs...> >
		{
			typedef indexor<PLs...> indexor_type;
			typedef vector_proxy_p<indexor_type> vector_proxy_type;
			return vector_proxy_type{ get_expression(*this) };
		}

		template <typename ... PLs>
		auto operator() (PLs ... pls) const
			->vector_proxy_cp < indexor<PLs...> >
		{
			typedef indexor<PLs...> indexor_type;
			typedef vector_proxy_cp<indexor_type> vector_proxy_type;
			return vector_proxy_type{ get_expression(*this) };
		}
	};

	template <typename ExprT>
	class vector_reference : 
		public vector_expression<vector_expression<ExprT> >
	{
		typedef vector_reference<ExprT> this_type;
	public:
		typedef ExprT refered_type;
		typedef typename refered_type::value_type value_type;
		typedef typename refered_type::const_reference const_reference;
		typedef std::conditional_t<std::is_const<refered_type>::value,
			typename refered_type::const_reference,
			typename refered_type::reference> reference;
		typedef typename refered_type::base_tag base_tag;
		static const size_type size = refered_type::size;
	public:

		vector_reference(refered_type& v)
			: vector_(v)
		{
		}

		reference operator() (size_type index)
		{
			return vector_(index);
		}

		const_reference operator() (size_type index) const
		{
			return vector_(index);
		}

		template <size_type Index>
		reference get()
		{
			static_assert(Index < size, "vector_reference::size");
			return vector_.get<Index>();
		}

		template <size_type Index>
		const_reference get() const
		{
			static_assert(Index < size, "vector_reference::size");
			return vector_.get<Index>();
		}

		template <typename ExprT>
		this_type& operator= (template_expression<ExprT> const& v)
		{
			vector_ = v;
			return *this;
		}

		template <typename ExprT>
		this_type& operator += (template_expression<ExprT> const& v)
		{
			vector_ += v;
			return *this;
		}

		template <typename ExprT>
		this_type& operator -= (template_expression<ExprT> const& v)
		{
			vector_ -= v;
			return *this;
		}

		template <typename ExprT>
		this_type& operator *= (template_expression<ExprT> const& v)
		{
			vector_ *= v;
			return *this;
		}

		template <typename ExprT>
		this_type& operator /= (template_expression<ExprT> const& v)
		{
			vector_ /= v;
			return *this;
		}

		bool same(this_type const& other)
		{
			return &vector_ == &other.vector_;
		}

	private:
		refered_type& vector_;
	};

	template <typename ExprT, typename IndexorT>
	class vector_proxy 
		: public vector_expression<vector_proxy<ExprT, IndexorT> >
	{
		typedef vector_proxy<ExprT, IndexorT> this_type;
	public:
		typedef ExprT refered_type;
		typedef typename refered_type::value_type value_type;
		typedef typename refered_type::const_reference const_reference;
		typedef std::conditional_t<std::is_const<refered_type>::value,
			typename refered_type::const_reference,
			typename refered_type::reference> reference;
		typedef typename refered_type::base_tag base_tag;
		typedef IndexorT indexor_type;
		static const size_type size = indexor_type::size;

		vector_proxy(refered_type& v)
			: vector_(v)
		{
		}

		template <size_type Index>
		reference get()
		{
			static_assert(Index < size, "vector_proxy::get");
			return vector_(indexor_type::get<Index>());
		}

		template <size_type Index>
		const_reference get() const
		{
			static_assert(Index < size, "vector_proxy::get");
			return vector_.get<indexor_type::get<Index>::value>();
		}

		using vector_expression<this_type>::operator();

	private:

		refered_type& vector_;
	};
} }
#pragma once

namespace leaves { namespace math 
{
	template <typename ExprT>
	class vector_expression : public template_expression<ExprT>
	{
	public:
		typedef ExprT expression_type;
		typedef std::add_const_t<ExprT> const_expression_type;

		template <typename ... PLs>
		auto operator() (PLs ... pls)
			->vector_proxy<expression_type, vector_indexor<PLs...> >
		{
			typedef vector_proxy<expression_type, vector_indexor<PLs...> > vector_proxy_type;
			return vector_proxy_type{ get_expression(*this) };
		}

		template <typename ... PLs>
		auto operator() (PLs ... pls) const
			->vector_proxy<const_expression_type, vector_indexor<PLs...> >
		{
			typedef vector_proxy<const_expression_type, vector_indexor<PLs...> > vector_proxy_type;
			return vector_proxy_type{ get_expression(*this) };
		}
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
			return vector_(indexor_type::get<Index>);
		}

		template <size_type Index>
		const_reference get() const
		{
			static_assert(Index < size, "vector_proxy::get");
			return vector_.get<indexor_type::get<Index>>();
		}

		using vector_expression<this_type>::operator();

	private:

		refered_type& vector_;
	};
} }
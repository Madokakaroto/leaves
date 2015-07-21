#pragma once

#include "vector_traits.hpp"
#include "vector_assign.hpp"
#include "vector_placholder.hpp"
#include "vector_expression.hpp"
#include "vector_operation.hpp"

namespace leaves { namespace math
{
	template <typename ScalarT, std::size_t Size, typename BaseT>
	class vector : public vector_expression<vector<ScalarT, Size, BaseT>>
	{
		typedef vector<ScalarT, Size, BaseT> this_type;
		typedef vector_expression<this_type> base_type;
	public:
		typedef std::enable_if_t<is_scalar<ScalarT>::value, ScalarT> value_type;
		typedef value_type& reference;
		typedef value_type const_reference;
		typedef value_type array_type[Size];
		typedef BaseT base_tag;
		static const size_type size = Size;
	
	public: /* constructors */

		vector() = default;

		explicit vector(const_reference uniform_value);

		template <typename Arg0, typename ... Args,
			typename = std::enable_if_t<check_ctor_param<size, Arg0, Args...>::value> >
		vector(Arg0 arg0, Args ... args)
			: base_type()
		{
			vector_assign_variadic<scalar_assign>(*this, arg0, args...);
		}

		vector(this_type const & other)
		{
			//data_ = other.data_;		// bite wise copy
			::memcpy(&data_, &other.data_, sizeof(value_type) * size);
		}

		template <typename ExprT>
		vector(vector_expression<ExprT> const& ve)
			: base_type()
		{
			vector_assign<scalar_assign>(*this, get_expression(ve));
		}

	public: /* operators with assign*/

		this_type& operator= (this_type const& other)
		{
			//data_ = other.data_;		// bite wise copy
			::memcpy(&data_, &other.data_, sizeof(value_type) * size);
			return *this;
		}

		template <typename ExprT>
		this_type& operator= (vector_expression<ExprT> const& ve)
		{
			vector_assign<scalar_assign>(*this, get_expression(ve));
			return *this
		}

		template <typename ExprT>
		this_type& operator += (vector_expression<ExprT> const& ve)
		{
			vector_assign<scalar_add_assign>(*this, get_expression(ve));
			return *this;
		}

		template <typename ExprT>
		this_type& operator -= (vector_expression<ExprT> const& ve)
		{
			vector_assign<scalar_sub_assign>(*this, get_expression(ve));
			return *this;
		}

		template <typename ExprT>
		this_type& operator *= (vector_expression<ExprT> const& ve)
		{
			vector_assign<scalar_mult_assign>(*this, get_expression(ve));
			return *this;
		}

		template <typename ExprT>
		this_type& operator /= (vector_expression<ExprT> const& ve)
		{
			vector_assign<scalar_div_assign>(*this, get_expression(ve));
			return *this;
		}

	public: /* index and proxy */

		value_type const* data() const
		{
			return &data_[0];
		}

		// dynamic indexing
		reference operator() (size_type index)
		{
			return data_[index];
		}

		// dynamic indexing
		const_reference operator() (size_type index) const
		{
			return data_[index];
		}

		// proxy
		using vector_expression<this_type>::operator();

		// static indexing
		template <size_type Index>
		reference get()
		{
			static_assert(Index < size, "vector::get");
			return data_[Index];
		}

		// static indexing
		template <size_type Index>
		const_reference get() const
		{
			static_assert(Index < size, "vector::get");
			return data_[Index];
		}

	private:

		array_type			data_;
	};
} }
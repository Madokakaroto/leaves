#pragma once

#include "traits.hpp"
#include "place_holder.hpp"
#include "evaluate.hpp"
#include "expression.hpp"
#include "functional.hpp"

namespace leaves { namespace math
{
	// T is represent a scalar type
	// B is short for base 
	template <typename T, size_type Size, typename B>
	class vector : public vector_expression<vector<T, Size, B> >
	{
		typedef vector<T, Size, B> this_type;
	public:
		static_assert(is_scalar<T>::value, "");
		typedef T value_type;
		typedef value_type& reference;
		typedef value_type array_type[Size];
		typedef B base_tag;
		static const size_type size = Size;
	public:

		/*
		 * default constructor
		 */
		vector() = default;

		/*
		 * one param constructor
		 */
		explicit vector(value_type v)
		{
			assign<scalar_assign>(*this, v);
		}
	
		/*
		 * size params constructor
		 */
		template <typename Arg0, typename ... Args,
			typename = std::enable_if_t<equal<size_type, argument_count<Arg0, Args...>::value, size>::value> >
		vector(Arg0 arg0, Args ... args)
		{
			assign<scalar_assign>(*this, arg0, args...);
		}
	
		/*
		 * copy constructor
		 */
		vector(this_type const & other)
		{
			// bit wise copy
			::memcpy(&data_, &other.data_, sizeof(value_type) * size);
		}
	
		/*
		 * evaluate when construct from another vector expression
		 */
		template <typename E_>
		vector(vector_expression<E_> const& ve)
		{
			assign<scalar_assign>(*this, ve);
		}
	
		/*
		 * copy assign
		 */
		this_type& operator= (this_type const& other)
		{
			// bite wise copy
			::memcpy(&data_, &other.data_, sizeof(value_type) * size);
			return *this;
		}
	
		/*
		 * evalutate when assign with another expression
		 */
		template <typename E_>
		this_type& operator= (vector_expression<E_> const& e)
		{
			assign<scalar_assign>(*this, get_expression(e));
			return *this;
		}
	
		/*
		 * add assign 
		 */
		template <typename E_>
		this_type& operator += (vector_expression<E_> const& e)
		{
			assign<scalar_add_assign>(*this, get_expression(e));
			return *this;
		}
	
		/*
		 * sub assign
		 */
		template <typename E_>
		this_type& operator -= (vector_expression<E_> const& e)
		{
			assign<scalar_sub_assign>(*this, get_expression(e));
			return *this;
		}
	
		/*
		 * multiply assign
		 */
		template <typename E_>
		this_type& operator *= (vector_expression<E_> const& e)
		{
			assign<scalar_mult_assign>(*this, get_expression(e));
			return *this;
		}
	
		/*
		 * divide assign
		 */
		template <typename E_>
		this_type& operator /= (vector_expression<E_> const& e)
		{
			assign<scalar_div_assign>(*this, get_expression(e));
			return *this;
		}

		/*
		 * scalar mult assign
		 */
		this_type& operator *= (value_type v)
		{
			return *this;
		}

		/*
		 * scalar divide assign
		 */
		this_type& operator /= (value_type v)
		{
			return *this;
		}

		// get the data buffer
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
		value_type operator() (size_type index) const
		{
			return data_[index];
		}

		// static indexing
		template <size_type Index>
		reference get()
		{
			static_assert(Index < size, "vector::get");
			return data_[Index];
		}

		// static indexing
		template <size_type Index>
		value_type get() const
		{
			static_assert(Index < size, "vector::get");
			return data_[Index];
		}

		// proxy
		using vector_expression<this_type>::operator();

	private:
		array_type			data_;
	};
} }
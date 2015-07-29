#pragma once

#include "traits.hpp"
#include "place_holder.hpp"
#include "functor.hpp"
#include "evaluate.hpp"
#include "expression.hpp"
#include "operator.hpp"

namespace leaves { namespace math
{
	// T is represent a scalar type
	// B is short for base 
	template <typename T, size_type Size, typename B>
	class vector : public vector_expression<vector<T, Size, B> >
	{
		typedef vector<T, Size, B> this_type;
	public:
		static_assert(is_scalar<T>::value, "Element must be a scalar type!");
		typedef T value_type;
		typedef value_type& reference;
		typedef value_type array_type[Size];
		typedef B base_tag;
		static size_type const size = Size;
		static size_type const complexity = 0u;		// no computation
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
			assign<vector_assign_scalar>(*this, v);
		}
	
		/*
		 * size params constructor
		 */
		template <typename Arg0, typename ... Args,
			typename = std::enable_if_t<equal<size_type, argument_count<Arg0, Args...>::value, size>::value> >
		vector(Arg0 arg0, Args ... args)
		{
			assign<vector_assign_scalar_variadic>(*this, arg0, args...);
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
		template <typename E1>
		vector(vector_expression<E1> const& ve)
		{
			assign<vector_assign_vector>(*this, ve);
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
		template <typename E1>
		this_type& operator= (vector_expression<E1> const& e)
		{
			assign<vector_assign_vector>(*this, get_expression(e));
			return *this;
		}
	
		/*
		 * add assign 
		 */
		template <typename E1>
		this_type& operator += (vector_expression<E1> const& e)
		{
			assign<vector_add_assign_vector>(*this, get_expression(e));
			return *this;
		}
	
		/*
		 * sub assign
		 */
		template <typename E1>
		this_type& operator -= (vector_expression<E1> const& e)
		{
			assign<vector_sub_assign_vector>(*this, get_expression(e));
			return *this;
		}
	
		/*
		 * multiply assign
		 */
		template <typename E1>
		this_type& operator *= (vector_expression<E1> const& e)
		{
			assign<vector_mult_assign_vector>(*this, get_expression(e));
			return *this;
		}
	
		/*
		 * divide assign
		 */
		template <typename E1>
		this_type& operator /= (vector_expression<E1> const& e)
		{
			assign<vector_div_assign_vector>(*this, get_expression(e));
			return *this;
		}

		/*
		 * scalar mult assign
		 */
		this_type& operator *= (value_type v)
		{
			assign<vector_mult_assign_scalar>(*this, v);
			return *this;
		}

		/*
		 * scalar divide assign
		 */
		this_type& operator /= (value_type v)
		{
			assign<vector_div_assign_scalar>(*this, v);
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
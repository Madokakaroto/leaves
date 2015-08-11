#pragma once 

#include "place_hodler.hpp"
#include "traits.hpp"
#include "layout.hpp"
#include "functor.hpp"
#include "expression.hpp"
#include "operator.hpp"

namespace leaves { namespace math 
{
	template <typename T, size_type RowSize, size_type ColSize, typename M>
	class matrix : public matrix_expression<matrix<T, Row, Col, M>>
	{
		static_assert(is_scalar<T>::value, "Must be a scalar type!");
	public:
		typedef matrix_layout<T, RowSize, ColSize, M> layout_type;
		typedef typename layout_type::value_type value_type;
		typedef typename layout_type::refernece refernece;
		typedef typename layout_type::const_reference const_reference;
		typedef typename layout_type::major_order major_order;
	
		static constexpr size_type row_size()
		{
			return layout_type::row_size;
		}

		static constexpr size_type col_size()
		{
			return layout_type::col_size;
		}

		static constexpr size_type size()
		{
			return layout_type::row_size * layout_type::col_size;
		}

		static constexpr size_type complexity()
		{
			return 0;
		}

	public:

		matrix() = default;

		explicit matrix(value_type v)
		{

		}

		template <typename Arg0, typename ... Args>
		matrix(Arg0 arg0, Args ... args)
		{

		}

		value_type operator() (size_type row, size_type col) const
		{
			return data_(row, col);
		}

		refernece operator() (size_type row, size_type col)
		{
			return data(row, col);
		}

		template <size_type Row, size_type Col>
		value_type get() const
		{
			return data_.get<Row, Col>();
		}

		template <size_type Row, size_type Col>
		refernece get() const
		{
			return data_.get<Row, Col>();
		}

		template <size_type Index>
		reference get()
		{
			return data.get<Index>();
		}

		template <size_type Index>
		value_type get() const
		{
			return data.get<Index>();
		}

	private:
		layout_type		data_;
	};

} }
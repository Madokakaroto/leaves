#pragma once 

#include "place_hodler.hpp"
#include "expression.hpp"

namespace leaves { namespace math 
{

	template <typename T, size_type Col, size_type Row, typename M>
	class matrix : public matrix_expression<matrix<T, Col, Row, M>>
	{
		static_assert(is_scalar<T>::value, "Must be a scalar type!");
	public:
		typedef T value_type;
		typedef value_type& reference;
		static size_type const col_size = Col;
		static size_type const row_size = Row;
		typedef M major_order;
		typedef value_type array_type[Col][Row];

	private:
		array_type		data_;
	};

	template <typename T, size_type Col, size_type Row>
	class matrix<T, Col, Row, row_major> :
		public matrix_expression<matrix<T, Col, Row, row_major> >
	{
		static_assert(is_scalar<T>::value, "Must be a scalar type!");
	public:
		typedef T value_type;
		typedef value_type& reference;
		typedef value_type constreference;
		static size_type const col_size = Col;
		static size_type const row_size = Row;
		typedef M major_order;
		typedef value_type array_type[Row][Col];
	
	public:

		matrix() = default;

		explicit matrix(value_type value);

		template <typename Arg0, typename ... Args>
		matrix(Arg0 arg0, Args ... args);

		reference operator() (size_type col, size_type row)
		{
			return data_[row][col];
		}

		constreference operator() (size_type col, size_type row) const
		{
			return data_[row][col];
		}

	private:
		array_type		data_;
	};

} }
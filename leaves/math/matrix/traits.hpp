#pragma once

namespace leaves { namespace math 
{
	/*
	 * Traits for place holders
	 */
	namespace matrix_detail
	{
		template <typename T>
		struct is_matrix_element_impl : std::false_type {};

		template <size_type Row, size_type Col>
		struct is_matrix_element_impl<matrix_element<Row, Col>> : std::true_type {};

		template <typename T>
		struct is_matrix_row_impl : std::false_type {};

		template <size_type Row>
		struct is_matrix_row_impl<matrix_row<Row>> : std::true_type {};

		template <typename T>
		struct is_matrix_col_impl : std::false_type {};

		template <size_type Col>
		struct is_matrix_col_impl<matrix_col<Col>> : std::true_type {};

		template <typename T>
		struct is_matrix_cofactor_impl : std::false_type {};

		template <size_type Row, size_type Col>
		struct is_matrix_cofactor_impl<matrix_cofactor<Row, Col>> : std::true_type {};
	}

	template <typename P>
	struct is_matrix_element : matrix_detail::is_matrix_element_impl<
		std::remove_const_t<std::remove_reference_t<P>>>
	{
	};

	template <typename P>
	struct is_matrix_row : matrix_detail::is_matrix_row_impl<
		std::remove_const_t<std::remove_reference_t<P>>>
	{
	};

	template <typename P>
	struct is_matrix_col : matrix_detail::is_matrix_col_impl<
		std::remove_const_t<std::remove_reference_t<P>>>
	{
	};

	template <typename P>
	struct is_matrix_cofactor : matrix_detail::is_matrix_cofactor_impl<
		std::remove_const_t<std::remove_reference_t<P>>>
	{
	};

	/*
	 * Traits for expression
	 */
	namespace matrix_detail
	{
		template <typename E>
		struct is_matrix_impl : std::false_type {};

		template <typename T, size_type RowSize, size_type ColSize, typename M>
		struct is_matrix_impl<matrix<T, RowSize, ColSize, M> > : std::true_type {};

		template <typename E>
		struct is_matrix_expression_impl : std::is_base_of<matrix_expression<E>, E>
		{
		};
	}

	// is matrix
	template <typename E>
	struct is_matrix : matrix_detail::is_matrix_impl<
		std::remove_const_t<std::remove_reference_t<E> > >
	{

	};

	// is matrix expression
	template <typename E>
	struct is_matrix_expression : matrix_detail::is_matrix_expression_impl<
		std::remove_const_t<std::remove_reference_t<E> > >
	{
	};

	template <typename M>
	struct major_to_base;

	template <>
	struct major_to_base<row_major>
	{
		typedef row_base type;
	};

	template <>
	struct major_to_base<col_major>
	{
		typedef col_base type;
	};

	template <typename M>
	using major_to_base_t = typename major_to_base<M>::type;
} }
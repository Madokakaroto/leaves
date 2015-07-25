#pragma once

#include <cmath>
#include <limits>
#include <algorithm>

namespace leaves { namespace math
{
	// expression type
	struct scalar_tag{};
	struct vector_tag{};
	struct matrix_tag{};

	struct col_base{};
	struct row_base{};

	template <typename ExprT>
	class template_expression;

	template <typename ExprT>
	class vector_expression;

	template <typename ScalarT, size_t Size, typename BaseT = col_base>
	class vector;

	template <typename ExprT>
	class vector_reference;

	template <typename ExprT, typename IndexorT>
	class vector_proxy;
} }
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

	// vector base tag
	struct col_base{};
	struct row_base{};

	// matrix major tag
	struct col_major{};
	struct row_major{};

	// template expression
	template <typename E>
	class template_expression;

	template <typename E>
	class scalar_expression;

	template <typename E>
	class vector_expression;

	template <typename E>
	class matrix_expression;

	template <typename T, size_t Size, typename B = col_base>
	class vector;

	template <typename E, typename I>
	class vector_proxy;

	template <typename E, typename F>
	class vector_unary;
} }
#pragma once

#define LEAVES_MATH_SCALAR_UNARY_OPERATOR(name, func) \
template <typename T> \
struct scalar_##name \
{ \
	typedef T value_type; \
	static value_type apply(value_type scalar) \
	{ \
		return func scalar; \
	} \
};

#define LEAVES_MATH_SCALAR_UNARY_FUNCTOR(name, func) \
template <typename T> \
struct scalar_##name \
{ \
	typedef T value_type; \
	static value_type apply(value_type scalar) \
	{ \
		return func(scalar); \
	} \
};

#define LEAVES_MATH_SCALAR_BINARY_OPERATOR(name, func) \
template <typename T1, typename T2> \
struct scalar_##name \
{ \
	typedef T1 l_value_type; \
	typedef T2 r_value_type; \
	typedef promotion_traits_t<l_value_type, r_value_type> return_type; \
	static return_type apply(l_value_type left, r_value_type right) \
	{ \
		return left func right; \
	} \
};

#define LEAVES_MATH_SCALAR_ASSIGN_OPERATOR(name, func) \
template <typename ScalarLeftT, typename ScalarRightT> \
struct scalar_##name \
{ \
	typedef ScalarLeftT l_value_type; \
	typedef ScalarRightT r_value_type; \
	static l_value_type apply(l_value_type& left, r_value_type right) \
	{ \
		return left func right; \
	} \
};

namespace leaves { namespace math 
{
	// unary operator
	LEAVES_MATH_SCALAR_UNARY_OPERATOR(negative, -);

	// unary functor
	LEAVES_MATH_SCALAR_UNARY_FUNCTOR(positive, leaves_numeric_positive);
	LEAVES_MATH_SCALAR_UNARY_FUNCTOR(squre, leaves_numeric_square);
	LEAVES_MATH_SCALAR_UNARY_FUNCTOR(abs, leaves_numeric_abs);
	LEAVES_MATH_SCALAR_UNARY_FUNCTOR(inverse, leaves_numeric_inverse);

	// binary operator
	LEAVES_MATH_SCALAR_BINARY_OPERATOR(add, +);
	LEAVES_MATH_SCALAR_BINARY_OPERATOR(sub, -);
	LEAVES_MATH_SCALAR_BINARY_OPERATOR(div, / );
	LEAVES_MATH_SCALAR_BINARY_OPERATOR(mult, *);

	// binary operator with assign
	LEAVES_MATH_SCALAR_ASSIGN_OPERATOR(assign, = );
	LEAVES_MATH_SCALAR_ASSIGN_OPERATOR(add_assign, += );
	LEAVES_MATH_SCALAR_ASSIGN_OPERATOR(sub_assign, -= );
	LEAVES_MATH_SCALAR_ASSIGN_OPERATOR(mult_assign, *= );
	LEAVES_MATH_SCALAR_ASSIGN_OPERATOR(div_assign, /= );
} }
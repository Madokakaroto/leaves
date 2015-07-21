#pragma once

#define LEAVES_MATH_SCALAR_UNARY_FUNCTOR(name, func) \
template <typename ScalarT> \
struct scalar_##name \
{ \
	typedef ScalarT value_type; \
	static value_type apply(value_type scalar) \
	{ \
	return  func scalar; \
	} \
};

#define LEAVES_MATH_SCALAR_BINARY_FUNCTOR(name, func) \
template <typename ScalarLeftT, typename ScalarRightT> \
struct scalar_##name \
{ \
	typedef ScalarLeftT l_value_type; \
	typedef ScalarRightT r_value_type; \
	typedef promotion_traits_t<l_value_type, r_value_type> return_type; \
	static return_type apply(l_value_type left, r_value_type right) \
	{ \
		return left func right; \
	} \
};

#define LEAVES_MATH_SCALAR_ASSIGN_FUNCTOR(name, func) \
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
	LEAVES_MATH_SCALAR_UNARY_FUNCTOR(positive, +);
	LEAVES_MATH_SCALAR_UNARY_FUNCTOR(negative, -);
	LEAVES_MATH_SCALAR_BINARY_FUNCTOR(add, +);
	LEAVES_MATH_SCALAR_BINARY_FUNCTOR(sub, -);
	LEAVES_MATH_SCALAR_BINARY_FUNCTOR(div, /);
	LEAVES_MATH_SCALAR_BINARY_FUNCTOR(mult, *);
	LEAVES_MATH_SCALAR_ASSIGN_FUNCTOR(assign, =);
	LEAVES_MATH_SCALAR_ASSIGN_FUNCTOR(add_assign, +=);
	LEAVES_MATH_SCALAR_ASSIGN_FUNCTOR(sub_assign, -= );
	LEAVES_MATH_SCALAR_ASSIGN_FUNCTOR(mult_assign, *= );
	LEAVES_MATH_SCALAR_ASSIGN_FUNCTOR(div_assign, /= );
} }
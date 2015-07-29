#pragma once

namespace leaves { namespace math 
{
	// assign
	template 
	<
		typename E1, typename E2,
		template <typename, typename> class BP		// BP is short for binary policy
	>
	struct vector_assign_vector_base
	{
		static_assert(is_vector_expression<E1>::value, "Must be a vector expression!");
		static_assert(is_vector_expression<E2>::value, "Must be a vector expression!");
		typedef E1 expression_type1;
		typedef E2 expression_type2;
		typedef typename expression_type1::value_type value_type1;
		typedef typename expression_type2::value_type value_type2;
		static size_type const size1 = expression_type1::size;
		static size_type const size2 = expression_type2::size;
		static_assert(size1 == size2, "Size must be the same!");
		static size_type const complexity2 = expression_type2::complexity;
		static_assert(complexity2 <= 1, "Too complex to calculate!");
		typedef BP<value_type1, value_type2> function_type;
		static size_type const size = size1;

		template <size_type B, size_type E>
		struct unroll
		{
			static void apply(expression_type1& e1, expression_type2 const& e2)
			{
				function_type::apply(e1.get<B>(), e2.get<B>());
				unroll<B + 1, E>::apply(e1, e2);
			}
		};

		template <size_type E>
		struct unroll<E, E>
		{
			static void apply(expression_type1& e1, expression_type2 const& e2)
			{
				function_type::apply(e1.get<E>(), e2.get<E>());
			}
		};

		static void apply(expression_type1& e1, expression_type2 const& e2)
		{
			unroll<0u, size - 1>::apply(e1, e2);
		}
	};

	template <typename E1, typename E2>
	using vector_assign_vector = vector_assign_vector_base<E1, E2, scalar_assign>;

	template <typename E1, typename E2>
	using vector_add_assign_vector = vector_assign_vector_base<E1, E2, scalar_add_assign>;

	template <typename E1, typename E2>
	using vector_sub_assign_vector = vector_assign_vector_base<E1, E2, scalar_sub_assign>;

	template <typename E1, typename E2>
	using vector_mult_assign_vector = vector_assign_vector_base<E1, E2, scalar_mult_assign>;

	template <typename E1, typename E2>
	using vector_div_assign_vector = vector_assign_vector_base<E1, E2, scalar_div_assign>;

	template
	<
		typename E, typename T,
		template <typename, typename> class BP
	>
	struct vector_assign_scalar_base
	{
		static_assert(is_vector_expression<E>::value, "Must be a vector expression!");
		static_assert(is_scalar<T>::value, "Must be a scalar type!");
		typedef E expression_type;
		typedef T scalar_type;
		typedef typename expression_type::value_type value_type;
		static size_type const size = expression_type::size;
		typedef BP<value_type, scalar_type> function_type;

		template <size_type B, size_type E>
		struct unroll
		{
			static void apply(expression_type& e, scalar_type t)
			{
				function_type::apply(e.get<B>(), t);
				unroll<B + 1, E>::apply(e, t);
			}
		};

		template <size_type E>
		struct unroll<E, E>
		{
			static void apply(expression_type& e, scalar_type t)
			{
				function_type::apply(e.get<E>(), t);
			}
		};

		static void apply(expression_type& e, scalar_type t)
		{
			unroll<0u, size - 1>::apply(e, t);
		}
	};

	template <typename E, typename T>
	using vector_assign_scalar = vector_assign_scalar_base<E, T, scalar_assign>;

	template <typename E, typename T>
	using vector_mult_assign_scalar = vector_assign_scalar_base<E, T, scalar_mult_assign>;

	template <typename E, typename T>
	using vector_div_assign_scalar = vector_assign_scalar_base<E, T, scalar_div_assign>;

	template <typename E, typename ... Args>
	struct vector_assign_scalar_variadic
	{
		static_assert(is_vector_expression<E>::value, "Must be a vector expression type!");
		typedef E expression_type;
		typedef is_same<Args...> same_types_traits;
		static_assert(same_types_traits::value, "Must be the same types!");
		typedef typename expression_type::value_type value_type;
		typedef typename same_types_traits::type scalar_type;
		typedef scalar_assign<value_type, scalar_type> function_type;
		static size_type const size1 = expression_type::size;
		static size_type const size2 = sizeof...(Args);
		static_assert(size1 == size2, "Must be the same size!");
		static size_type const size = size1;

		template <size_type B, size_type E>
		struct unroll
		{
			static void apply(expression_type& e, Args ... args)
			{
				function_type::apply(e.get<B>(), argument<B>::get(args...));
				unroll<B + 1, E>::apply(e, args...);
			}
		};

		template <size_type E>
		struct unroll<E, E>
		{
			static void apply(expression_type& e, Args ... args)
			{
				function_type::apply(e.get<E>(), argument<E>::get(args...));
			}
		};

		static void apply(expression_type& e, Args ... args)
		{
			unroll<0, size - 1>::apply(e, args...);
		}
	};

	// unary
	template 
	<
		typename E,
		template <typename> class UP	// UP is short for unary policy
	>
	struct vector_unary_functor_base
	{
	private:
		static_assert(is_vector_expression<E>::value, "Must be a vector expression!");
		typedef E expression_type;
		typedef typename expression_type::value_type evalue_type;
		static_assert(expression_type::complexity <= 1, "To complex to calculate!");
		
		template <size_type C> // C is short for complexity
		struct complex
		{
			static size_type const value = C;
		};

		template <>
		struct complex<0u>
		{
			static size_type const value = 1u;
		};

	public:
		typedef UP<evalue_type> function_type;
		typedef typename function_type::value_type value_type;
		typedef value_type reference;
		typedef expression_type base_tag;
		static size_type const size = expression_type::size;
		static size_type const complexity = complex<expression_type::complexity>::value;

		template <size_type I>
		static value_type apply(expression_type& e)
		{
			return function_type::apply(e.get<I>());
		}

		static value_type apply(expression_type& e, size_type i)
		{
			return function_type::apply(e(i));
		}
	};

	// something wrong with template alias
	//template <typename E>
	//using vector_unary_positive = vector_unary_functor_base<E, scalar_positive>;
	//template <typename E>
	//using vector_unary_negative = vector_unary_functor_base<E, scalar_negative>;
	//template <typename E>
	//using vector_unary_abs = vector_unary_functor_base<E, scalar_abs>;
	//template <typename E>
	//using vector_unary_square = vector_unary_functor_base<E, scalar_square>;
	//template <typename E>
	//using vector_unary_inverse = vector_unary_functor_base<E, scalar_inverse>;
	template <typename E>
	struct vector_unary_positive : vector_unary_functor_base<E, scalar_positive> {};
	template <typename E>
	struct vector_unary_negative : vector_unary_functor_base<E, scalar_negative> {};
	template <typename E>
	struct vector_unary_abs : vector_unary_functor_base<E, scalar_abs> {};
	template <typename E>
	struct vector_unary_square : vector_unary_functor_base<E, scalar_square> {};
	template <typename E>
	struct vector_unary_inverse : vector_unary_functor_base<E, scalar_inverse> {};

	template 
	<
		typename E1, typename E2, 
		template <typename, typename> class BP
	>
	struct vector_binary_functor_base
	{
	private:
		static_assert(is_vector_expression<E1>::value, "Must be a vector expression!");
		static_assert(is_vector_expression<E2>::value, "Must be a vector expression!");
		typedef E1 expression_type1;
		typedef E2 expression_type2;
		typedef typename expression_type1::value_type value_type1;
		typedef typename expression_type2::value_type value_type2;
		typedef typename expression_type1::base_tag base_tag1;
		typedef typename expression_type2::base_tag base_tag2;
		static_assert(std::is_same<base_tag1, base_tag2>::value, "Must have the same base tag!");
		static size_type const size1 = expression_type1::size;
		static size_type const size2 = expression_type2::size;
		static_assert(size1 == size2, "Must have the same size!");
		static size_type const complexity1 = expression_type1::complexity;
		static size_type const complexity2 = expression_type2::complexity;
		static_assert(complexity1 <= 1, "To complex to calculate!");
		static_assert(complexity2 <= 1, "To complex to calculate!");
		static size_type const larger_complexity = max<size_type, complexity1, complexity2>::value;

		template <size_type C> // C is short for complexity
		struct complex
		{
			static size_type const value = C;
		};

		template <>
		struct complex<0u>
		{
			static size_type const value = 1u;
		};
		
	public:
		typedef BP<value_type1, value_type2> function_type;
		typedef typename function_type::return_type value_type;
		typedef value_type reference;
		typedef base_tag1 base_tag;
		static size_type const size = size1;
		static size_type const complexity = complex<larger_complexity>::value;

		template <size_type I>
		static value_type apply(expression_type1& e1, expression_type2& e2)
		{
			return function_type::apply(e1.get<I>(), e2.get<I>());
		}

		static value_type apply(expression_type1& e1, expression_type2& e2, size_type i)
		{
			return function_type::apply(e1(i), e2(i));
		}
	};

	//template <typename E1, typename E2>
	//using vector_binary_add = vector_binary_functor_base<E1, E2, scalar_add>;
	//template <typename E1, typename E2>
	//using vector_binary_sub = vector_binary_functor_base<E1, E2, scalar_sub>;
	//template <typename E1, typename E2>
	//using vector_binary_mult = vector_binary_functor_base<E1, E2, scalar_mult>;
	//template <typename E1, typename E2>
	//using vector_binary_div = vector_binary_functor_base<E1, E2, scalar_div>;
	template <typename E1, typename E2>
	struct vector_binary_add : vector_binary_functor_base<E1, E2, scalar_add> {};
	template <typename E1, typename E2>
	struct vector_binary_sub : vector_binary_functor_base<E1, E2, scalar_sub> {};
	template <typename E1, typename E2>
	struct vector_binary_mult : vector_binary_functor_base<E1, E2, scalar_mult> {};
	template <typename E1, typename E2>
	struct vector_binary_div : vector_binary_functor_base<E1, E2, scalar_div> {};

	template
	<
		typename E1, typename T,
		template <typename, typename> class BP
	>
	struct vector_scalar_functor_base
	{
	private:
		static_assert(is_vector_expression<E1>::value, "Must be a vector type!");
		static_assert(is_scalar<T>::value, "Must be a scalar type!");
		typedef E1 exprssion_type;
		typedef typename exprssion_type::value_type evalue_type;
		typedef T scalar_type;
		static_assert(exprssion_type::complexity <= 1, "Too complex to calculate!");

		template <size_type C>
		struct complex
		{
			static size_type const value = C;
		};

		template <>
		struct complex<0u>
		{
			static size_type const value = 1u;
		};

	public:
		typedef BP<evalue_type, scalar_type> function_type;
		typedef typename function_type::return_type value_type;
		typedef value_type reference;
		typedef typename exprssion_type::base_tag base_tag;
		static size_type const size = exprssion_type::size;
		static size_type const complexity = complex<exprssion_type::complexity>::value;

		template <size_type I>
		static value_type apply(exprssion_type& e, scalar_type t)
		{
			return function_type::apply(e.get<I>(), t);
		}

		static value_type apply(exprssion_type& e, scalar_type t, size_type i)
		{
			return function_type::apply(e(i), t);
		}
	};

	//template <typename E, typename T>
	//using vector_scalar_mult = vector_scalar_functor_base<E, T, scalar_mult>;
	//template <typename E, typename T>
	//using vector_scalar_div = vector_scalar_functor_base<E, T, scalar_div>;
	template <typename E, typename T>
	struct vector_scalar_mult : vector_scalar_functor_base<E, T, scalar_mult> {};
	template <typename E, typename T>
	struct vector_scalar_div : vector_scalar_functor_base<E, T, scalar_div> {};

} }
#pragma once

namespace leaves { namespace math 
{
	template 
	<
		typename E1, typename E2,
		template <typename, typename> class BP		// BP is short for binary policy
	>
	struct vector_assign_vector_base
	{
		typedef E1 expression_type1;
		typedef E2 expression_type2;
		static size_type const size1 = expression_type1::size;
		static size_type const size2 = expression_type2::size;
		static_assert(size1 == size2, "Size must be the same!");
		static size_type const size = size1;
		typedef typename expression_type1::value_type value_type1;
		typedef typename expression_type2::value_type value_type2;
		typedef BP<value_type1, value_type2> function_type;

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
		struct unroll
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
} }
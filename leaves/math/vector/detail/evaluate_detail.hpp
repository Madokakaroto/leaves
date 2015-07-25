#pragma once

namespace leaves { namespace math 
{
	namespace vector_detail
	{
		// evaluate_vector_with_vector
		template <typename Func, typename E1, typename E2>
		struct vector_assign_vector
		{
			typedef Func function_type;
			typedef E1 left_expression_type;
			typedef E2 right_expression_type;
			static size_type const size_left = left_expression_type::size;
			static size_type const size_right = right_expression_type::size;	
			static_assert(size_left == size_right, "Illegal evaluation between tow vectors with different size!");
			static size_type const size = size_left;

			template <size_type Begin, size_type End>
			struct unroll
			{
				static_assert(Begin < End, "Begin >= End");

				static void apply(left_expression_type& e1, right_expression_type const& e2)
				{
					function_type::apply(e1.get<Begin>(), e2.get<Begin>());
					unroll<Begin + 1, End>::apply(e1, e2);
				}
			};

			template <size_type End>
			struct unroll<End, End>
			{
				static void apply(left_expression_type& e1, right_expression_type const& e2)
				{
					function_type::apply(e1.get<End>(), e2.get<End>());
				}
			};

			static void apply(left_expression_type& e1, right_expression_type const& e2)
			{
				unroll<0, size - 1>::apply(e1, e2);
			}
		};

		// evaluate_vector_with_scalar
		template <typename Func, typename E, typename T>
		struct vector_assign_scalar
		{
			typedef Func function_type;
			typedef E expression_type;
			typedef T scalar_type;
			static size_type const size = expression_type::size;

			template <size_type Begin, size_type End>
			struct unroll
			{
				static_assert(Begin < End, "Begin >= End");

				static void apply(expression_type& e, scalar_type scalar)
				{
					function_type::apply(e.get<Begin>(), scalar);
					unroll<Begin + 1, End>::apply(e, scalar);
				}
			};

			template <size_type End>
			struct unroll<End, End>
			{
				static void apply(expression_type& e, scalar_type scalar)
				{
					function_type::apply(e.get<End>(), scalar);
				}
			};

			static void apply(expression_type& e, scalar_type scalar)
			{
				unroll<0, size - 1>::apply(e, scalar);
			}
		};

		// evaluate_vector_with_scalar_variadic
		template <typename Func, typename E, typename ... Args>
		struct vector_assign_scalar_variadic
		{
			typedef Func function_type;
			typedef E expression_type;
			typedef typename is_same<Args...> same_traits_type;
			static_assert(same_traits_type::value, "Must be the same type!");
			typedef typename same_traits_type::type scalar_type;
			static size_type const expression_size = expression_type::size;
			static size_type const scalar_size = sizeof...(Args);
			static_assert(expression_size == scalar_size, "Evaluation must have size the same!");
			static size_type const size = expression_size;

			template <size_type Begin, size_type End>
			struct unroll
			{
				static_assert(Begin < End, "Begin >= End");

				static void apply(expression_type& e, Args ... args)
				{
					function_type::apply(e.get<Begin>(), argument<Begin>::get(args...));
					unroll<Begin + 1, End>::apply(e, args...);
				}
			};

			template <size_type End>
			struct unroll<End, End>
			{
				static void apply(expression_type& e, Args ... args)
				{
					function_type::apply(e.get<End>(), argument<End>::get(args...));
				}
			};

			static void apply(expression_type& e, Args ... args)
			{
				unroll<0, size - 1>::apply(e, args...);
			}
		};

		// evaluate_vector_to_scalar
		template 
		<
			typename E,
			template <typename, typename> class ScalarBinary
		>
		struct vector_reduce_scalar
		{
			typedef E expression_type;
			typedef typename expression_type::value_type value_type;
			typedef ScalarBinary<value_type, value_type> function_type;
			typedef typename function_type::return_type return_type;
			static size_type const size = expression_type::size;

			template <size_type Begin, size_type End>
			struct unroll
			{
				static_assert(Begin < End, "Begin >= End");

				static return_type apply(expression_type const& e)
				{
					return function_type::apply(e.get<Begin>(), unroll<Begin + 1, End>::apply(e));
				}
			};

			template <size_type End>
			struct unroll<End, End>
			{
				static return_type apply(expression_type const& e)
				{
					return e.get<End>();
				}
			};

			static return_type apply(expression_type const& e)
			{
				return unroll<0, size - 1>::apply(e);
			}
		};

		template 	
		<
			typename E, 
			template <typename> class ScalarUnary,
			template <typename, typename> class ScalarBinary
		>
		struct vector_reduce_scalar_ex
		{
			typedef E expression_type;
			typedef typename expression_type::value_type value_type;
			typedef ScalarUnary<value_type> unary_function;
			typedef ScalarBinary<value_type, value_type> binary_function;
			typedef typename binary_function::return_type return_type;
			static size_type const size = expression_type::size;

			template <size_type Begin, size_type End>
			struct unroll
			{
				static_assert(Begin < End, "Begin >= End");

				static return_type apply(expression_type const& e)
				{
					return binary_function::apply(
						unary_function::apply(e.get<Begin>()), unroll<Begin + 1, End>::apply(e)
					);
				}
			};

			template <size_type End>
			struct unroll<End, End>
			{
				static return_type apply(expression_type const& e)
				{
					return unary_function::apply(e.get<End>());
				}
			};

			static return_type apply(expression_type const& e)
			{
				return unroll<0, size - 1>::apply(e);
			}
		};

		template
		<
			typename E1, typename E2,
			template <typename, typename> class ScalarBinary1,
			template <typename, typename> class ScalarBinary2
		>
		struct vector_binary_reduce_scalar
		{
			typedef E1 left_expression_type;
			typedef E2 right_expression_type;
			typedef typename left_expression_type::value_type left_value_type;
			typedef typename right_expression_type::value_type right_value_type;
			typedef ScalarBinary1<left_value_type, right_value_type> function_type1;
			typedef ScalarBinary2<left_value_type, right_value_type> function_type2;
			typedef typename function_type2::return_type return_type;
			static size_type const left_size = left_expression_type::size;
			static size_type const right_size = right_expression_type::size;
			static_assert(left_size == right_size, "Size must be same!");
			static size_type const size = left_size;

			template <size_type Begin, size_type End>
			struct unroll
			{
				static_assert(Begin < End, "Begin >= End");

				static return_type apply(left_expression_type const& e1, right_expression_type const& e2)
				{
					return function_type2::apply(
						function_type1::apply(e1.get<Begin>(), e2.get<Begin>()),
						unroll<Begin + 1, End>::apply(e1, e2)
					);
				}
			};

			template <size_type End>
			struct unroll<End, End>
			{
				static return_type apply(left_expression_type const& e1, right_expression_type const& e2)
				{
					return function_type1::apply(e1.get<End>(), e2.get<End>());
				}
			};

			static return_type apply(left_expression_type const& e1, right_expression_type const& e2)
			{
				return unroll<0, size - 1>::apply(e1, e2);
			}
		};
	}
} }
#pragma once

namespace leaves { namespace math 
{
	namespace vector_detail
	{
		// evaluate_vector_with_vector
		template <typename Func, typename E1, typename E2>
		struct evaluate_vector_with_vector
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

				static void apply(left_expression_type&& e1, right_expression_type&& e2)
				{
					function_type::apply(
						get<Begin>(std::forward<left_expression_type>(e1)),
						get<Begin>(std::forward<right_expression_type>(e2)));

					unroll<Begin + 1, End>::apply(
						std::forward<left_expression_type>(e1), 
						std::forward<right_expression_type>(e2));
				}
			};

			template <size_type End>
			struct unroll<End, End>
			{
				static void apply(left_expression_type&& e1, right_expression_type&& e2)
				{
					function_type::apply(
						get<End>(std::forward<left_expression_type>(e1)),
						get<End>(std::forward<right_expression_type>(e2)));
				}
			};

			static void apply(left_expression_type&& e1, right_expression_type&& e2)
			{
				unroll<0, size - 1>::apply(
					std::forward<left_expression_type>(e1),
					std::forward<right_expression_type>(e2));
			}
		};

		// evaluate_vector_with_scalar
		template <typename Func, typename E, typename T>
		struct evaluate_vector_with_scalar
		{
			typedef Func function_type;
			typedef E expression_type;
			typedef T scalar_type;
			static size_type const size = expression_type::size;

			template <size_type Begin, size_type End>
			struct unroll
			{
				static_assert(Begin < End, "Begin >= End");

				static void apply(expression_type&& e, scalar_type scalar)
				{
					function_type::apply(get<Begin>(std::forward<expression_type>(e)), scalar);

					unroll<Begin + 1, End>::apply(std::forward<expression_type>(e), scalar);
				}
			};

			template <size_type End>
			struct unroll<End, End>
			{
				static void apply(expression_type&& e, scalar_type scalar)
				{
					function_type::apply(get<End>(std::forward<expression_type>(e)), scalar);
				}
			};

			static void apply(expression_type&& e, scalar_type scalar)
			{
				unroll<0, size - 1>::apply(std::forward<expression_type>(e), scalar);
			}
		};

		// evaluate_vector_with_scalar_variadic
		template <typename Func, typename E, typename ... Args>
		struct evaluate_vector_with_scalar_variadic
		{
			typedef Func function_type;
			typedef E expression_type;
			typedef typename is_same<Args...>::type, scalar_type;
			static size_type const expression_size = expression_type::size;
			static size_type const scalar_size = sizeof...(Args);
			static_assert(expression_size == scalar_size, "Evaluation must have size the same!");
			static size_type const size = expression_size;

			template <size_type Begin, size_type End>
			struct unroll
			{
				static_assert(Begin < End, "Begin >= End");

				static void apply(expression_type&& e, Args ... args)
				{
					function_type::apply(get<Begin>(
						get<Begin>(std::forward<expression_type>(e)), 
						argument<Begin>::get(args...));

					unroll<Begin + 1, End>::apply(std::forward<expression_type>(e), args...);
				}
			};

			template <size_type End>
			struct unroll<End, End>
			{
				static void apply(expression_type&& e, Args ... args)
				{
					function_type::apply(get<Begin>(
						get<End>(std::forward<expression_type>(e)),
						argument<End>::get(args...));
				}
			};
		};

		// evaluate_vector_to_scalar
		template <typename Func, typename E>
		struct evaluate_vector_to_scalar
		{
			typedef Func function_type;
			typedef E expression_type;
			typedef typename expression_type::value_type result_type;
			static size_type const size = expression_type::size;

			template <size_type Begin, size_type End>
			struct unroll
			{
				static_assert(Begin < End, "Begin >= End");

				static result_type apply(expression_type const& e, result_type init)
				{
					return function_type::apply(get<Begin>(e), unroll<Begin + 1, End>::apply(e, init));
				}
			};

			template <size_type End>
			struct unroll<End, End>
			{
				static result_type apply(expression_type const& e, result_type init)
				{
					return function_type::apply(get<End>(e), init);
				}
			};

			static result_type apply(expression_type const& e, result_type init)
			{
				return unroll<0, size - 1>::apply(e, init);
			}
		};
	}
} }
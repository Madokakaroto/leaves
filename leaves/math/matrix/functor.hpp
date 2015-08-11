#pragma once

namespace leaves { namespace math 
{
	template
	<
		typename E1, typename E2,
		template <typename, typename> class BP
	>
	struct matrix_assign_matrix_base
	{
		static_assert(is_matrix_expression<E1>::value "Must be a matrix expression type!");
		static_assert(is_matrix_expression<E2>::value "Must be a matrix expression type!");
		static_assert(E1::row_size() == E2::row_size(), "Row size must be the same!");
		static_assert(E1::col_size() == E2::col_size(), "Col size must be the same!");
		static_assert(E1::complexity() == 0, "Too complex to calculate!");
		static_assert(E2::complexity() <= 1, "Too complex to calculate!");

		typedef E1 expression_type1;
		typedef E2 expression_type2;
		typedef typename expression_type1::value_type value_type1;
		typedef typename expression_type2::value_type value_type2;
		typedef BP<value_type1, value_type2> function_type;

		static constexpr size_type row_size()
		{
			return expression_type1::row_size();
		}

		static constexpr size_type col_size()
		{
			return expression_type1::col_size();
		}

		template <size_type RowBegin, size_type RowEnd, size_type ColBegin, size_type ColEnd>
		struct unroll
		{
			static void apply(expression_type1& e1, expression_type2 const& e2)
			{
				function_type::apply(e1.get<RowBegin, ColBegin>(), e2.get<RowBegin, ColBegin>());
				unroll<RowBegin, RowEnd, ColBegin + 1, ColEnd>::apply(e1, e2);
			}
		};

		template <size_type RowBegin, size_type RowEnd, size_type ColEnd>
		struct unroll<RowBegin, RowEnd, ColEnd, ColEnd>
		{
			static void apply(expression_type1& e1, expression_type2 const& e2)
			{
				function_type::apply(e1.get<RowBegin, ColEnd>(), e2.get<RowBegin, ColEnd>());
				unroll<RowBegin + 1, RowEnd, 0, RowEnd>::apply(e1, e2);
			}
		};

		template <size_type RowEnd, size_type ColEnd>
		struct unroll<RowEnd, RowEnd, ColEnd, ColEnd>
		{
			static void apply(expression_type1& e1, expression_type2 const& e2)
			{
				function_type::apply(e1.get<RowEnd, ColEnd>(), e2.get<RowEnd, ColEnd>());
			}
		};

		static void apply(expression_type1& e1, expression_type2 const& e2)
		{
			unroll<0, row_size() - 1, 0, col_size() - 1>::apply(e1, e2);
		}
	};

	template <typename E1, typename E2>
	using matrix_assign_matrix = matrix_assign_matrix_base<E1, E2, scalar_assign>;
	template <typename E1, typename E2>
	using matrix_add_assign_matrix = matrix_assign_matrix_base<E1, E2, scalar_add_assign>;
	template <typename E1, typename E2>
	using matrix_sub_assign_matrix = matrix_assign_matrix_base<E1, E2, scalar_sub_assign>;

	template 
	<
		typename E, typename T,
		template <typename, typename> class BP
	>
	struct matrix_assign_scalar_base
	{
		static_assert(is_matrix_expression<E>::value, "Must be a matrix expression!");
		static_assert(is_scalar<T>::value, "Must be a scalar type!");
		static_assert(E::complexity() == 0, "Too complex to assign!");

		typedef E expression_type;
		typedef typename expression_type::value_type value_type1;
		typedef T value_type2;
		typedef BP<value_type1, value_type2> function_type;

		static constexpr size_type row_size()
		{
			return expression_type::row_size();
		}

		static constexpr size_type col_size()
		{
			return expression_type::col_size();
		}

		template <size_type RowBegin, size_type RowEnd, size_type ColBegin, size_type ColEnd>
		struct unroll
		{
			static void apply(expression_type& e, value_type2 t)
			{
				function_type::apply(e.get<RowBegin, ColBegin>(), t);
				unroll<RowBegin, RowEnd, ColBegin + 1, ColEnd>::apply(e, t);
			}
		};

		template <size_type RowBegin, size_type RowEnd, size_type ColEnd>
		struct unroll<RowBegin, RowEnd, ColEnd, ColEnd>
		{
			static void apply(expression_type& e, value_type2 t)
			{
				function_type::apply(e.get<RowBegin, ColEnd>(), t);
				unroll<RowBegin + 1, RowEnd, 0, RowEnd>::apply(e, t);
			}
		};

		template <size_type RowEnd, size_type ColEnd>
		struct unroll<RowEnd, RowEnd, ColEnd, ColEnd>
		{
			static void apply(expression_type& e, value_type2 t)
			{
				function_type::apply(e.get<RowEnd, ColEnd>(), t);
			}
		};

		static void apply(expression_type& e, value_type2 t)
		{
			unroll<0, row_size() - 1, 0, col_size() - 1>::apply(e, t);
		}
	};

	template <typename E, typename T>
	using matrix_assign_scalar = matrix_assign_scalar_base<E, T, scalar_assign>;
	template <typename E, typename T>
	using matrix_mult_assign_scalar = matrix_assign_scalar_base<E, T, scalar_mult_assign>;
	template <typename E, typename T>
	using matrix_div_assign_scalar = matrix_assign_scalar_base<E, T, scalar_div_assign>;

	template <typename E, typename ... Args>
	struct matrix_assign_scalar_variadic
	{
		static_assert(is_matrix_expression<E>::value, "Must be a matrix expression!");
		typedef is_same<Args...> is_same_type;
		static_assert(is_same_type::value, "Must be the same type!");
		typedef typename is_same_type::type scalar_type;
		static_assert(is_scalar<T>::value, "Must be a scalar type!");
		static_assert(sizeof...(Args) == E::size(), "Must have the same size!");
		typedef E expression_type;
		typedef typename expression_type::value_type evalue_type;
		typedef scalar_assign<evalue_type, scalar_type> funciton_type;

		static constexpr size_type size()
		{
			return expression_type::size();
		}
		
		template <size_type Begin, size_type End>
		struct unroll
		{
			static void apply(expression_type& e, Args ... args)
			{
				funciton_type::apply(e.get<Begin>(), argument<Begin>::get(args...));
				unroll<Begin + 1, End>::apply(e, args...);
			}
		};

		template <size_type End>
		struct unroll<End, End>
		{
			static void apply(expression_type& e, Args ... args)
			{
				funciton_type::apply(e.get<End>(), argument<End>::get(args...));
			}
		};

		static void apply(expression_type& e, Args ... args)
		{
			unroll<0, size() - 1>::apply(e, args...);
		}
	};

	template <typename E1, typename E2>
	struct matrix_assign_matrix_complex
	{
		static_assert(is_matrix_expression<E1>::value "Must be a matrix expression type!");
		static_assert(is_matrix_expression<E2>::value "Must be a matrix expression type!");
		static_assert(E1::row_size() == E2::row_size(), "Row size must be the same!");
		static_assert(E1::col_size() == E2::col_size(), "Col size must be the same!");
		static_assert(E1::complexity() == 0, "Too complex to calculate!");
		static_assert(E2::complexity() == 4, "Too complex to calculate!");

		typedef E1 expression_type1;
		typedef E2 expression_type2;
		typedef typename expression_type1::major_order major_order;
		typedef typename expression_type1::value_type value_type1;
		typedef typename expression_type2::value_type value_type2;
		typedef scalar_assign<value_type1, value_type2> function_type;

		static constexpr size_type row_size()
		{
			return expression_type1::row_size();
		}

		static constexpr size_type col_size()
		{
			return expression_type1::col_size();
		}

		//template <

		static void apply(expression_type1& e1, expression_type2 const& e2)
		{

		}
	};
} }
#pragma once

namespace leaves{ namespace math 
{
	namespace vector_detail
	{
		template <typename FuncT, typename LeftExprT, typename RightExprT>
		struct assign_impl
		{
			static const size_t l_size = LeftExprT::size;
			static const size_t r_size = RightExprT::size;
			static const size_t size = l_size == r_size ? l_size : 0;

			template <size_t Begin, size_t End>
			struct unroll
			{
				static_assert(Begin < End, "");

				static void apply(LeftExprT& left, RightExprT const& right)
				{
					FuncT::apply(get<Begin>(left), get<Begin>(right));
					unroll<Begin + 1, End>::apply(left, right);
				}
			};

			template <size_t End>
			struct unroll<End, End>
			{
				static void apply(LeftExprT& left, RightExprT const& right)
				{
					FuncT::apply(get<End>(left), get<End>(right));
				}
			};

			static auto apply(LeftExprT& left, RightExprT const& right)
				->std::enable_if_t<size != 0>
			{
				unroll<0, size - 1>::apply(left, right);
			}
		};

		template <size_t Index>
		struct argument
		{
			template <typename Arg0, typename ... Args>
			static auto get(Arg0 arg0, Args ... args)
				-> decltype(argument<Index - 1>::get(args...))
			{
				return argument<Index - 1>::get(args...);
			}
		};

		template <>
		struct argument<0>
		{
			template <typename Arg0, typename ... Args>
			static Arg0 get(Arg0 arg0, Args ... args)
			{
				return arg0;
			}
		};

		template <typename FuncT, typename VectorT, typename ... Args>
		struct assign_variadic_impl
		{
			static const size_t l_size = VectorT::size;
			static const size_t r_size = sizeof...(Args);
			static const size_t size = l_size == r_size ? l_size : 0;

			template <size_t Begin, size_t End>
			struct unroll
			{
				static_assert(Begin < End, "");

				static void apply(VectorT& v, Args ... args)
				{
					FuncT::apply(v(Begin), argument<Begin>::get(args...));
					unroll<Begin + 1, End>::apply(v, args...);
				}
			};

			template <size_t End>
			struct unroll<End, End>
			{
				static void apply(VectorT& v, Args ... args)
				{
					FuncT::apply(v(End), argument<End>::get(args...));
				}
			};

			static auto apply(VectorT& v, Args... args)
				-> std::enable_if_t<size != 0>
			{
				unroll<0, size - 1>::apply(v, args...);
			}
		};
	}

	template
	<
		template <typename T1, typename T2> class Func,
		typename LeftT, typename RightT
	>
	void vector_assign(vector_expression<LeftT>& left, vector_expression<RightT> const& right)
	{
		typedef LeftT left_expr_type;
		typedef RightT right_expr_type;
		typedef typename left_expr_type::value_type l_value_type;
		typedef typename right_expr_type::value_type r_value_type;
		typedef Func<l_value_type, r_value_type> functor_type;

		typedef vector_detail::assign_impl<functor_type,
			left_expr_type, right_expr_type> impl_type;

		impl_type::apply(get_expression(left), get_expression(right));
	}

	template 
	<
		template <typename T1, typename T2> class Func,
		typename ExprT, typename ... Args
	>
	void vector_assign_variadic(vector_expression<ExprT>& vec, Args ... args)
	{
		typedef ExprT vector_expr_type;
		typedef check_ctor_param<vector_expr_type::size, Args...> check_type;
		typedef typename vector_expr_type::value_type l_value_type;
		typedef typename check_type::type r_value_type;
		typedef Func<l_value_type, r_value_type> functor_type;

		typedef vector_detail::assign_variadic_impl<functor_type,
			vector_expr_type, Args...> impl_type;

		impl_type::apply( get_expression(vec), args...);
	}
} }
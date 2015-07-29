#pragma once

namespace leaves { namespace math
{
	template <size_type M, size_type N>
	struct matrix_place_holder
	{
		static size_type const col = M;
		static size_type const row = N;
	};

	namespace placeholders
	{
		static matrix_place_holder<0, 0> _11;
		static matrix_place_holder<0, 1> _12;
		static matrix_place_holder<0, 2> _13;
		static matrix_place_holder<0, 3> _14;

		static matrix_place_holder<1, 0> _21;
		static matrix_place_holder<1, 1> _22;
		static matrix_place_holder<1, 2> _23;
		static matrix_place_holder<1, 3> _24;

		static matrix_place_holder<2, 0> _31;
		static matrix_place_holder<2, 1> _32;
		static matrix_place_holder<2, 2> _33;
		static matrix_place_holder<2, 3> _34;

		static matrix_place_holder<3, 0> _41;
		static matrix_place_holder<3, 1> _42;
		static matrix_place_holder<3, 2> _43;
		static matrix_place_holder<3, 3> _44;
	}
} }
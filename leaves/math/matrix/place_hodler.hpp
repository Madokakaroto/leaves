#pragma once

namespace leaves { namespace math
{
	template <size_type Row, size_type Col>
	struct matrix_element
	{
		static constexpr size_type row()
		{
			return Row;
		}

		static constexpr size_type col()
		{
			return Col;
		}
	};

	template <size_type Row>
	struct matrix_row
	{
		static constexpr size_type row()
		{
			return Row;
		}
	};

	template <size_type Col>
	struct matrix_col
	{
		static constexpr size_type col()
		{
			return Col;
		}
	};

	template <size_type Row, size_type Col>
	struct matrix_cofactor
	{
		static constexpr size_type row()
		{
			return Row;
		}

		static constexpr size_type col()
		{
			return Col;
		}
	};

	namespace placeholders
	{
		static matrix_element<0, 0> _11;
		static matrix_element<0, 1> _12;
		static matrix_element<0, 2> _13;
		static matrix_element<0, 3> _14;

		static matrix_element<1, 0> _21;
		static matrix_element<1, 1> _22;
		static matrix_element<1, 2> _23;
		static matrix_element<1, 3> _24;

		static matrix_element<2, 0> _31;
		static matrix_element<2, 1> _32;
		static matrix_element<2, 2> _33;
		static matrix_element<2, 3> _34;

		static matrix_element<3, 0> _41;
		static matrix_element<3, 1> _42;
		static matrix_element<3, 2> _43;
		static matrix_element<3, 3> _44;

		static matrix_row<0> _r1;
		static matrix_row<1> _r2;
		static matrix_row<2> _r3;
		static matrix_row<3> _r4;

		static matrix_col<0> _c1;
		static matrix_col<1> _c2;
		static matrix_col<2> _c3;
		static matrix_col<3> _c4;

		static matrix_cofactor<0, 0> _m11;
		static matrix_cofactor<0, 1> _m12;
		static matrix_cofactor<0, 2> _m13;
		static matrix_cofactor<0, 3> _m14;

		static matrix_cofactor<1, 0> _m21;
		static matrix_cofactor<1, 1> _m22;
		static matrix_cofactor<1, 2> _m23;
		static matrix_cofactor<1, 3> _m24;

		static matrix_cofactor<2, 0> _m31;
		static matrix_cofactor<2, 1> _m32;
		static matrix_cofactor<2, 2> _m33;
		static matrix_cofactor<2, 3> _m34;

		static matrix_cofactor<3, 0> _m41;
		static matrix_cofactor<3, 1> _m42;
		static matrix_cofactor<3, 2> _m43;
		static matrix_cofactor<3, 3> _m44;
	}
} }
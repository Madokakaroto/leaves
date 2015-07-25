#pragma once

namespace leaves { namespace math
{
	template <size_type Index>
	struct vector_place_holder
	{
		enum
		{
			value = Index,
		};
	};

	namespace placeholders
	{
		static vector_place_holder<0> _r;
		static vector_place_holder<1> _g;
		static vector_place_holder<2> _b;
		static vector_place_holder<3> _a;

		static vector_place_holder<0> _1;
		static vector_place_holder<1> _2;
		static vector_place_holder<2> _3;
		static vector_place_holder<3> _4;

		static vector_place_holder<0> _x;
		static vector_place_holder<1> _y;
		static vector_place_holder<2> _z;
		static vector_place_holder<3> _w;
	}

	template <typename PL>
	struct is_vector_place_holder : std::false_type {};

	template <size_type Index>
	struct is_vector_place_holder<vector_place_holder<Index> >
		: std::true_type
	{
	};

	template <typename PL, typename ... PLs>
	struct check_vector_place_hodlers
	{
		static const bool value = is_vector_place_holder<PL>::value &&
			check_vector_place_hodlers<PLs...>::value;
	};

	template <typename PL>
	struct check_vector_place_hodlers<PL>
	{
		static const bool value = is_vector_place_holder<PL>::value;
	};

	// begin place hodler
	template <typename ... PLs>
	struct vector_indexor
	{
		typedef make_type_list_t<PLs...> place_hodlers;

		static size_type const size = sizeof...(PLs);

		template <size_type Index>
		struct get
		{
			static_assert(Index < size, "indexor::get");
			typedef typelist::type_at_t<place_hodlers, Index> place_holder_type;
			static size_type const value = place_holder_type::value;
		};
	};
} }
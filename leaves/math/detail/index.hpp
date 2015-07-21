#pragma once

#include <assert.h>

namespace leaves { namespace math 
{
	// begin place hodler
	template <typename ... PLs>
	struct indexor
	{
		typedef make_type_list_t<PLs...> place_hodlers;

		static const size_t size = sizeof...(PLs);

		//template <size_t Index>
		//static size_t const get()
		//{
		//	static_assert(Index < size, "indexor::get");
		//
		//	typedef typelist::type_at_t<place_hodlers, Index> place_holder_type;
		//	return place_holder_type::value;
		//}

		template <size_t Index>
		struct get
		{
			static_assert(Index < size, "indexor::get");
			typedef typelist::type_at_t<place_hodlers, Index> place_holder_type;
			static const size_t value = place_holder_type::value;
		};
	};
} }
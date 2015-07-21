#pragma once
#include "null_type.hpp"

// type list
namespace leaves
{
	template <typename Head, typename Tail>
	struct type_list
	{
		typedef Head head_t;
		typedef Tail tail_t;
	};

	// make type list
	template <typename Head = null_type, typename ... Rests>
	struct make_type_list
	{
		typedef type_list<Head, typename make_type_list<Rests...>::type> type;
	};

	template <>
	struct make_type_list<>
	{
		typedef null_type type;
	};

	template <typename ... Args>
	using make_type_list_t = typename make_type_list<Args...>::type;

	namespace typelist
	{
		// length
		template <typename TL>
		struct length {};

		template <>
		struct length<null_type>
		{
			enum { value = 0 };
		};

		template <typename Head, typename Tail>
		struct length<type_list<Head, Tail> >
		{
			enum { value = 1 + length<Tail>::value };
		};

		// type at
		namespace tl_detail
		{
			template <typename TL, size_t Size>
			struct type_at_impl {};

			template <typename Head, typename Tail, size_t Index>
			struct type_at_impl<type_list<Head, Tail>, Index>
				: type_at_impl<Tail, Index - 1>
			{

			};

			template <typename Head, typename Tail>
			struct type_at_impl<type_list<Head, Tail>, 0>
			{
				typedef Head type;
			};
		}

		template <typename TL, size_t Index>
		struct type_at_strict : tl_detail::type_at_impl < TL, Index >
		{
			static_assert(Index < length<TL>::value, "Index access violation!");
		};

		template <typename TL, size_t Index>
		using type_at_strict_t = typename type_at_strict<TL, Index>::type;

		template <typename TL, size_t Index, typename Default = null_type,
			bool = Index >= 0 && (length<TL>::value > Index)>
		struct type_at
		{
			typedef Default type;
		};

		template <typename TL, size_t Index, typename Default>
		struct type_at<TL, Index, Default, true> : tl_detail::type_at_impl<TL, Index>{};
		
		template <typename TL, size_t Index, typename Default = null_type>
		using type_at_t = typename type_at<TL, Index, Default>::type;
		
		// index of 
		template <typename TL, typename T>
		struct index_of {};
		
		template <typename T>
		struct index_of<null_type, T>
		{
			enum { value = -1 };
		};
		
		template <typename T, typename Tail>
		struct index_of<type_list<T, Tail>, T>
		{
			enum { value = 0 };
		};
		
		template <typename Head, typename Tail, typename T>
		struct index_of<type_list<Head, Tail>, T>
		{
		private:
			enum { temp = index_of<Tail, T>::value };
		public:
			enum { value = (temp == -1) ? -1 : 1 + temp };
		};
		
		// has type
		template <typename TL, typename T>
		struct has_type
		{
			static bool const value = index_of<TL, T>::value >= 0;
		};
		
		// apped
		template <typename TL, typename T>
		struct append { };
		
		template<>
		struct append<null_type, null_type>
		{
			typedef null_type type;
		};
		
		template <typename T>
		struct append<null_type, T>
		{
			typedef type_list<T, null_type> type;
		};
		
		template <typename Head, typename Tail>
		struct append<null_type, type_list<Head, Tail> >
		{
			typedef type_list<Head, Tail> type;
		};
		
		template <typename Head, typename Tail, typename T>
		struct append<type_list<Head, Tail>, T>
		{
			typedef type_list<Head, typename append<Tail, T>::type> type;
		};
		
		template <typename TL, typename T>
		using append_t = typename append<TL, T>::type;
		
		// erase
		template <typename TL, typename T>
		struct erase { };
		
		template <typename T, typename Tail>
		struct erase<type_list<T, Tail>, T>
		{
			typedef Tail type;
		};
		
		template <typename Head, typename Tail, typename T>
		struct erase<type_list<Head, Tail>, T>
		{
			typedef type_list<Head, typename erase<Tail, T>::type> type;
		};
		
		template <typename TL, typename T>
		using erase_t = typename erase<TL, T>::type;
		
		// erase all
		template <typename TL, typename T>
		struct erase_all {};
		
		template <typename T>
		struct erase_all<null_type, T>
		{
			typedef null_type type;
		};
		
		template <typename Tail, typename T>
		struct erase_all<type_list<T, Tail>, T>
		{
			typedef typename erase_all<Tail, T>::type type;
		};
		
		template <typename Head, typename Tail, typename T>
		struct erase_all<type_list<Head, Tail>, T>
		{
			typedef type_list<Head, typename erase_all<Tail, T>::type> type;
		};
		
		template <typename TL, typename T>
		using erase_all_t = typename erase_all<TL, T>::type;
		
		// no duplicates
		template <typename TL>
		struct no_duplicates {};
		
		template <>
		struct no_duplicates<null_type>
		{
			typedef null_type type;
		};
		
		template <typename Head, typename Tail>
		struct no_duplicates<type_list<Head, Tail> >
		{
			typedef type_list<Head, typename erase<typename no_duplicates<Tail>::type, Head>::type> type;
		};
		
		template <typename TL>
		using no_duplicates_t = typename no_duplicates<TL>::type;
		
		// replace
		template <typename TL, typename T, typename U>
		struct replace {};
		
		template <typename T, typename U>
		struct replace<null_type, T, U>
		{
			typedef null_type type;
		};
		
		template <typename Tail, typename T, typename U>
		struct replace<type_list<T, Tail>, T, U>
		{
			typedef type_list<U, Tail> type;
		};
		
		template <typename Head, typename Tail, typename T, typename U>
		struct replace<type_list<Head, Tail>, T, U>
		{
			typedef type_list<Head, typename replace<Tail, T, U>::type> type;
		};
		
		template <typename TL, typename T, typename U>
		using replace_t = typename replace<TL, T, U>::type;
		
		template <typename TL, typename T, typename U>
		struct replace_all {};
		
		template <typename T, typename U>
		struct replace_all<null_type, T, U>
		{
			typedef null_type type;
		};
		
		template <typename Tail, typename T, typename U>
		struct replace_all<type_list<T, Tail>, T, U>
		{
			typedef type_list<U, typename replace_all<Tail, T, U>::type> type;
		};
		
		template <typename Head, typename Tail, typename T, typename U>
		struct replace_all<type_list<Head, Tail>, T, U>
		{
			typedef type_list<Head, typename replace_all<Tail, T, U>::type> type;
		};
		
		template <typename TL, typename T, typename U>
		using replace_all_t = typename replace_all<TL, T, U>::type;
		
		// reverse
		template <typename TL>
		struct reverse {};
		
		template <>
		struct reverse<null_type>
		{
			typedef null_type type;
		};
		
		template <typename Head, typename Tail>
		struct reverse<type_list<Head, Tail> >
		{
			typedef typename append<typename reverse<Tail>::type, Head>::type type;
		};
		
		template <typename TL>
		using reverse_t = typename reverse<TL>::type;
	}
}
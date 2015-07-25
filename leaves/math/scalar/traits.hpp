#pragma once

namespace leaves { namespace math 
{
	typedef std::size_t size_type;

	namespace scalar_traits_detail
	{
		template <typename T>
		struct next_type;

		template <>
		struct next_type<float>
		{
			typedef double type;
		};

		template <>
		struct next_type<double>
		{
			typedef long double type;
		};
	}

	template <typename T>
	struct scalar_tratis
	{
		typedef scalar_tratis self_type;
		typedef T value_type;
		typedef T const& const_reference;
		typedef T& reference;
		typedef value_type precision_type;

		static const unsigned plus_complesxity = 1;
		static const unsigned multiplies_complexity = 1;

		static value_type abs(const_reference t)
		{
			return leaves_numeric_abs(t);
		}

		static value_type sqrt(const_reference t)
		{
			return value_type{ leaves_numeric_sqrt(t) };
		}

		static value_type norm_1(const_reference t)
		{
			return self_type::abs(t);
		}

		static value_type norm_2(const_reference t)
		{
			return self_type::abs(t);
		}

		static value_type norm_inf(const_reference t)
		{
			return self_type::abs(t);
		}

		static auto equal(const_reference lhs, const_reference rhs)
			-> std::enable_if_t<std::is_floating_point<T>::value>
		{
			return self_type::norm_inf(lhs - rhs) < self_type::sqrt(std::numeric_limits<value_type>::epsilon()) *
				std::max(std::max(self_type::norm_inf(lhs), self_type::norm_inf(rhs)),
				self_type::sqrt(std::numeric_limits<value_type>::min()));
		}

		static auto equal(const_reference lhs, const_reference rhs)
			-> std::enable_if_t<!std::is_floating_point<T>::value>
		{
			return lhs == rhs;
		}
	};

	template <typename T>
	struct type_traits : scalar_tratis<T> { };

	template <size_t I, typename ScalarT>
	auto get(ScalarT scalar)
		->std::enable_if_t<is_scalar<ScalarT>::value, ScalarT>
	{
		return scalar;
	}
} }
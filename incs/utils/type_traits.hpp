/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:44:18 by dohelee           #+#    #+#             */
/*   Updated: 2021/12/06 15:47:49 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft
{
	template<bool Cond, class T = void>
	struct enable_if {}; //reference : https://modoocode.com/255

	template<class T>
	struct enable_if<true, T>
	{ 
		typedef T type;
	};

	template <class T, T v>
	struct integral_constant {
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
	};

	/// The type used as a compile-time boolean with true value.
	typedef integral_constant<bool, true> true_type;
	/// The type used as a compile-time boolean with false value.
	typedef integral_constant<bool, false> false_type;

	template <typename T>
	struct is_integral : public false_type {};

	template <>
	struct is_integral<bool> : public true_type {};
	template <>
	struct is_integral<char> : public true_type {};
	template <>
	struct is_integral<wchar_t> : public true_type {};
	template <>
	struct is_integral<signed char> : public true_type {};
	template <>
	struct is_integral<short int> : public true_type {};
	template <>
	struct is_integral<int> : public true_type {};
	template <>
	struct is_integral<long int> : public true_type {};
	template <>
	struct is_integral<long long int> : public true_type {};
	template <>
	struct is_integral<unsigned char> : public true_type {};
	template <>
	struct is_integral<unsigned short int> : public true_type {};
	template <>
	struct is_integral<unsigned int> : public true_type {};
	template <>
	struct is_integral<unsigned long int> : public true_type {};
	template <>
	struct is_integral<unsigned long long int>	: public true_type {};

	template <>
	struct is_integral<const bool> : public true_type {};
	template <>
	struct is_integral<const char> : public true_type {};
	template <>
	struct is_integral<const wchar_t> : public true_type {};
	template <>
	struct is_integral<const signed char> : public true_type {};
	template <>
	struct is_integral<const short int> : public true_type {};
	template <>
	struct is_integral<const int> : public true_type {};
	template <>
	struct is_integral<const long int> : public true_type {};
	template <>
	struct is_integral<const long long int> : public true_type {};
	template <>
	struct is_integral<const unsigned char> : public true_type {};
	template <>
	struct is_integral<const unsigned short int> : public true_type {};
	template <>
	struct is_integral<const unsigned int> : public true_type {};
	template <>
	struct is_integral<const unsigned long int> : public true_type {};
	template <>
	struct is_integral<const unsigned long long int> : public true_type {};

	// char16_t and char32_t only since c++11...
	// template <> struct is_integral<char16_t> : public true_type {};
	// template <> struct is_integral<char32_t> : public true_type {};

	// Compare for equality of types.
	template<typename, typename>
	struct are_same
	{
		enum { value = 0 };
		typedef false_type type;
	};

	template<typename T>
	struct are_same<T, T>
	{
		enum { value = 1 };
		typedef true_type type;
	};
};

#endif
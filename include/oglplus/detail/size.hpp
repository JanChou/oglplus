/**
 *  .file oglplus/detail/size.hpp
 *  .brief Implementation of wrapper for sizei
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#ifndef OGLPLUS_DETAIL_SIZE_1501311633_HPP
#define OGLPLUS_DETAIL_SIZE_1501311633_HPP

#include <oglplus/config/compiler.hpp>
#include <type_traits>
#include <stdexcept>
#include <cstddef>
#include <limits>
#include <new>

namespace oglplus {

template <typename T>
struct SizeImpl
{
private:
	T _v;

	template <typename R, typename X>
	static
	typename std::enable_if<(sizeof(R) <= sizeof(X)), R>::type
	_chkin2(X v)
	{
		if(v > X(std::numeric_limits<T>::max()))
		{
			throw std::domain_error("Size value too big");
		}
		return R(v);
	}

	template <typename R, typename X>
	static
	typename std::enable_if<(sizeof(R) > sizeof(X)), R>::type
	_chkin2(X v)
	{
		return R(v);
	}

	template <typename R, typename X>
	static inline
	typename std::enable_if<std::is_signed<X>::value, R>::type
	_chkin1(X v)
	{
		if(v < X(0))
		{
			throw std::domain_error("Negative size value");
		}
		return _chkin2<R>(v);
	}

	template <typename R, typename X>
	static inline
	typename std::enable_if<!std::is_signed<X>::value, R>::type
	_chkin1(X v)
	{
		return _chkin2<R>(v);
	}

	template <typename X>
	static inline
	T _checkin(X v)
	{
		return _chkin1<T>(v);
	}

	template <typename X>
	static
	typename std::enable_if<(sizeof(T) <= sizeof(X)), T>::type
	_cv_in1(X v)
	OGLPLUS_NOEXCEPT(true)
	{
		if(v > X(std::numeric_limits<T>::max()))
		{
			return T(-1);
		}
		return T(v);
	}

	template <typename X>
	static
	typename std::enable_if<(sizeof(T) > sizeof(X)), T>::type
	_cv_in1(X v)
	OGLPLUS_NOEXCEPT(true)
	{
		return T(v);
	}

	template <typename X>
	static inline
	T _conv_in(X v)
	OGLPLUS_NOEXCEPT(true)
	{
		return _cv_in1(v);
	}
public:
	SizeImpl(void)
	OGLPLUS_NOEXCEPT(true)
	 : _v(T(0))
	{ }

	template <typename X>
	SizeImpl(
		X v,
		typename std::enable_if<
			std::is_integral<X>::value
		>::type* = nullptr
	): _v(_checkin(v))
	{ }

	SizeImpl(T v, std::nothrow_t)
	OGLPLUS_NOEXCEPT(true)
	 : _v(v)
	{ }

	template <typename X>
	SizeImpl(
		X v,
		std::nothrow_t,
		typename std::enable_if<
			std::is_integral<X>::value
		>::type* = nullptr
	) OGLPLUS_NOEXCEPT(true)
	 : _v(_conv_in(v))
	{ }

	T get(void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return _v;
	}

	OGLPLUS_EXPLICIT
	operator bool (void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return _v >= T(0);
	}

	bool operator ! (void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return _v < T(0);
	}

	operator T (void) const
	OGLPLUS_NOEXCEPT(true)
	{
		return _v;
	}

	template <typename X>
	OGLPLUS_EXPLICIT
	operator X (void) const
	{
		return _chkin1<X>(_v);
	}

	friend bool operator == (SizeImpl s1, SizeImpl s2)
	OGLPLUS_NOEXCEPT(true)
	{
		return s1._v == s2._v;
	}

	friend bool operator == (T v, SizeImpl s)
	OGLPLUS_NOEXCEPT(true)
	{
		return v == s._v;
	}

	friend bool operator == (SizeImpl s, T v)
	OGLPLUS_NOEXCEPT(true)
	{
		return s._v == v;
	}


	friend bool operator != (SizeImpl s1, SizeImpl s2)
	OGLPLUS_NOEXCEPT(true)
	{
		return s1._v != s2._v;
	}

	friend bool operator != (T v, SizeImpl s)
	OGLPLUS_NOEXCEPT(true)
	{
		return v != s._v;
	}

	friend bool operator != (SizeImpl s, T v)
	OGLPLUS_NOEXCEPT(true)
	{
		return s._v != v;
	}


	friend bool operator <  (SizeImpl s1, SizeImpl s2)
	OGLPLUS_NOEXCEPT(true)
	{
		return s1._v <  s2._v;
	}

	friend bool operator <  (T v, SizeImpl s)
	OGLPLUS_NOEXCEPT(true)
	{
		return v <  s._v;
	}

	friend bool operator <  (SizeImpl s, T v)
	OGLPLUS_NOEXCEPT(true)
	{
		return s._v <  v;
	}


	friend bool operator <= (SizeImpl s1, SizeImpl s2)
	OGLPLUS_NOEXCEPT(true)
	{
		return s1._v <= s2._v;
	}

	friend bool operator <= (T v, SizeImpl s)
	OGLPLUS_NOEXCEPT(true)
	{
		return v <= s._v;
	}

	friend bool operator <= (SizeImpl s, T v)
	OGLPLUS_NOEXCEPT(true)
	{
		return s._v <= v;
	}


	friend bool operator >  (SizeImpl s1, SizeImpl s2)
	OGLPLUS_NOEXCEPT(true)
	{
		return s1._v >  s2._v;
	}

	friend bool operator >  (T v, SizeImpl s)
	OGLPLUS_NOEXCEPT(true)
	{
		return v >  s._v;
	}

	friend bool operator >  (SizeImpl s, T v)
	OGLPLUS_NOEXCEPT(true)
	{
		return s._v >  v;
	}


	friend bool operator >= (SizeImpl s1, SizeImpl s2)
	OGLPLUS_NOEXCEPT(true)
	{
		return s1._v >= s2._v;
	}

	friend bool operator >= (T v, SizeImpl s)
	OGLPLUS_NOEXCEPT(true)
	{
		return v >= s._v;
	}

	friend bool operator >= (SizeImpl s, T v)
	OGLPLUS_NOEXCEPT(true)
	{
		return s._v >= v;
	}


	friend T operator + (SizeImpl s1, SizeImpl s2)
	OGLPLUS_NOEXCEPT(true)
	{
		return s1._v + s2._v;
	}

	friend T operator + (SizeImpl s, T v)
	OGLPLUS_NOEXCEPT(true)
	{
		return s._v + v;
	}

	friend T operator + (T v, SizeImpl s)
	OGLPLUS_NOEXCEPT(true)
	{
		return v + s._v;
	}

	friend T operator * (SizeImpl s1, SizeImpl s2)
	OGLPLUS_NOEXCEPT(true)
	{
		return s1._v * s2._v;
	}

	friend T operator * (SizeImpl s, T v)
	OGLPLUS_NOEXCEPT(true)
	{
		return s._v * v;
	}

	friend T operator * (T v, SizeImpl s)
	OGLPLUS_NOEXCEPT(true)
	{
		return v * s._v;
	}

	friend T operator / (SizeImpl s1, SizeImpl s2)
	OGLPLUS_NOEXCEPT(true)
	{
		return s1._v / s2._v;
	}

	friend T operator / (SizeImpl s, T v)
	OGLPLUS_NOEXCEPT(true)
	{
		return s._v / v;
	}

	friend T operator / (T v, SizeImpl s)
	OGLPLUS_NOEXCEPT(true)
	{
		return v / s._v;
	}

	friend T operator % (SizeImpl s1, SizeImpl s2)
	OGLPLUS_NOEXCEPT(true)
	{
		return s1._v % s2._v;
	}

	friend T operator % (SizeImpl s, T v)
	OGLPLUS_NOEXCEPT(true)
	{
		return s._v % v;
	}

	friend T operator % (T v, SizeImpl s)
	OGLPLUS_NOEXCEPT(true)
	{
		return v % s._v;
	}
};

} // namespace oglplus

#endif // include guard

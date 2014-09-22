//  File implement/eglplus/enums/config_caveat_range.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/eglplus/config_caveat.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2014 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
EGLPLUS_LIB_FUNC aux::CastIterRange<
	const EGLenum*,
	ConfigCaveat
> ValueRange_(ConfigCaveat*)
#if (!EGLPLUS_LINK_LIBRARY || defined(EGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(EGLPLUS_IMPL_EVR_CONFIGCAVEAT)
#define EGLPLUS_IMPL_EVR_CONFIGCAVEAT
{
static const EGLenum _values[] = {
#if defined EGL_NONE
EGL_NONE,
#endif
#if defined EGL_SLOW_CONFIG
EGL_SLOW_CONFIG,
#endif
#if defined EGL_NON_CONFORMANT_CONFIG
EGL_NON_CONFORMANT_CONFIG,
#endif
0
};
return aux::CastIterRange<
	const EGLenum*,
	ConfigCaveat
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#else
;
#endif
} // namespace enums


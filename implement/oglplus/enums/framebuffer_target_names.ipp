//  File implement/oglplus/enums/framebuffer_target_names.ipp
//
//  Automatically generated file, DO NOT modify manually.
//  Edit the source 'source/enums/oglplus/framebuffer_target.txt'
//  or the 'source/enums/make_enum.py' script instead.
//
//  Copyright 2010-2014 Matus Chochlik.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
namespace enums {
OGLPLUS_LIB_FUNC StrCRef ValueName_(
	FramebufferTarget*,
	GLenum value
)
#if (!OGLPLUS_LINK_LIBRARY || defined(OGLPLUS_IMPLEMENTING_LIBRARY)) && \
	!defined(OGLPLUS_IMPL_EVN_FRAMEBUFFERTARGET)
#define OGLPLUS_IMPL_EVN_FRAMEBUFFERTARGET
{
switch(value)
{
#if defined GL_DRAW_FRAMEBUFFER
	case GL_DRAW_FRAMEBUFFER: return StrCRef("DRAW_FRAMEBUFFER");
#endif
#if defined GL_READ_FRAMEBUFFER
	case GL_READ_FRAMEBUFFER: return StrCRef("READ_FRAMEBUFFER");
#endif
	default:;
}
OGLPLUS_FAKE_USE(value);
return StrCRef();
}
#else
;
#endif
} // namespace enums


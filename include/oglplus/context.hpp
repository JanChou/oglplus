/**
 *  @file oglplus/context.hpp
 *  @brief Declaration of OpenGL's state wrapper
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_CONTEXT_1107121317_HPP
#define OGLPLUS_CONTEXT_1107121317_HPP

#include <oglplus/context/synchronization.hpp>

#include <oglplus/context/capabilities.hpp>
#include <oglplus/context/viewport.hpp>
#include <oglplus/context/buffer_selection.hpp>
#include <oglplus/context/buffer_masking.hpp>
#include <oglplus/context/clear_buffers.hpp>
#include <oglplus/context/rasterization.hpp>
#include <oglplus/context/drawing.hpp>
#include <oglplus/context/depth_test.hpp>
#include <oglplus/context/stencil_test.hpp>
#include <oglplus/context/blending.hpp>
#include <oglplus/context/logical_ops.hpp>
#include <oglplus/context/scissor_test.hpp>

#include <oglplus/face_mode.hpp>
#include <oglplus/compare_func.hpp>


namespace oglplus {

/// Namespace containing definitions of GL context-related operation wrappers
namespace context { }

/** @defgroup ogl_context Current OpenGL context operations
 *
 *  Here are listed classes and functions wrapping operations on the current
 *  OpenGL context, which are not related to any explicitly allocated
 *  object or resource, i.e. operations like enabling and disabling
 *  various OpenGL oglplus::Capability "capabilities" and changing the state
 *  values of the current context.
 */

/// Wrapper for the current OpenGL context operations
/**
 *  @ingroup ogl_context
 */
class Context
 : public context::Capabilities
 , public context::ViewportOps
 , public context::BufferSelection
 , public context::BufferMasking
 , public context::ClearBuffers
 , public context::Rasterization
 , public context::Drawing
 , public context::DepthTest
 , public context::StencilTest
 , public context::ScissorTest
 , public context::LogicalOps
 , public context::Blending
 , public context::Synchronization
{
public:
};

} // namespace oglplus

#endif // include guard

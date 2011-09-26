/**
 *  @example oglplus/006_cartoon_sun.cpp
 *  @brief Shows how to render a rectangle with an animated sun drawing
 *
 *  @image html 006_cartoon_sun.png
 *
 *  Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>

#include "example.hpp"

#include <cmath>

namespace oglplus {

class RectangleExample : public Example
{
private:
	// wrapper around the current OpenGL context
	Context gl;

	// Vertex shader
	VertexShader vs;

	// Fragment shader
	FragmentShader fs;

	// Program
	Program prog;

	// A vertex array object for the rendered rectangle
	VertexArray rectangle;

	// VBOs for the rectangle's vertices used also as the viewport coords
	Buffer verts;
public:
	RectangleExample(void)
	{
		// Set the vertex shader source
		vs.Source(
			"#version 330\n"
			"in vec2 Position;"
			"out vec2 vertPos;"
			"void main(void)"
			"{"
			"	gl_Position = vec4(Position, 0.0, 1.0);"
			"	vertPos = gl_Position.xy;"
			"}"
		);
		// compile it
		vs.Compile();

		// set the fragment shader source
		fs.Source(
			"#version 330\n"
			"uniform float Time;"
			"uniform vec2 SunPos;"
			"uniform vec3 Sun1, Sun2, Sky1, Sky2;"
			"in vec2 vertPos;"
			"out vec3 fragColor;"
			"void main(void)"
			"{"
			"	vec2 v = vertPos - SunPos;"
			"	float l = length(v);"
			"	float a = atan(v.y, v.x)/3.1415;"
			"	if(l < 0.1)"
			"		fragColor = Sun1;"
			"	else if(int(18*(Time*0.1 + 1.0 + a)) % 2 == 0)"
			"		fragColor = mix(Sun1, Sun2, l);"
			"	else"
			"		fragColor = mix(Sky1, Sky2, l);"
			"}"
		);
		// compile it
		fs.Compile();

		// attach the shaders to the program
		prog.AttachShader(vs);
		prog.AttachShader(fs);
		// link and use it
		prog.Link();
		prog.Use();

		// bind the VAO for the rectangle
		rectangle.Bind();

		GLfloat rectangle_verts[8] = {
			-1.0f, -1.0f,
			-1.0f,  1.0f,
			 1.0f, -1.0f,
			 1.0f,  1.0f
		};
		// bind the VBO for the rectangle vertices
		verts.Bind(Buffer::Target::Array);
		// upload the data
		Buffer::Data(Buffer::Target::Array, 8, rectangle_verts);
		// setup the vertex attribs array for the vertices
		VertexAttribArray vert_attr(prog, "Position");
		vert_attr.Setup(2, DataType::Float);
		vert_attr.Enable();
		//
		Uniform(prog, "Sun1").Set(0.95f, 0.85f, 0.60f);
		Uniform(prog, "Sun2").Set(0.90f, 0.80f, 0.20f);
		Uniform(prog, "Sky1").Set(0.90f, 0.80f, 0.50f);
		Uniform(prog, "Sky2").Set(0.80f, 0.60f, 0.40f);
		//
		gl.ClearDepth(1.0f);
	}

	void Reshape(size_t width, size_t height)
	{
		gl.Viewport(width, height);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();

		auto angle = FullCircles(time * 0.05f);
		Uniform(prog, "Time").Set(GLfloat(time));
		Uniform(prog, "SunPos").Set(
			-Cos(angle),
			Sin(angle)
		);
		gl.DrawArrays(PrimitiveType::TriangleStrip, 0, 4);
	}

	bool Continue(double time)
	{
		return time < 30.0;
	}
};

std::unique_ptr<Example> makeExample(void)
{
	return std::unique_ptr<Example>(new RectangleExample);
}

} // namespace oglplus

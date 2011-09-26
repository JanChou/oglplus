/**
 *  @example oglplus/021_wooden_crate.cpp
 *  @brief Shows how to draw a simple textured and bump mapped cube
 *
 *  @image html 021_wooden_crate.png
 *
 *  Copyright 2008-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/shapes/cube.hpp>
#include <oglplus/images/load.hpp>
#include <oglplus/images/normal_map.hpp>
#include <oglplus/bound/texture.hpp>

#include <cmath>

#include "example.hpp"

namespace oglplus {

class CubeExample : public Example
{
private:
	// helper object building cube vertex attributes
	shapes::Cube make_cube;
	// helper object encapsulating cube drawing instructions
	shapes::DrawingInstructions cube_instr;
	// indices pointing to cube primitive elements
	shapes::Cube::IndexArray cube_indices;

	// wrapper around the current OpenGL context
	Context gl;

	// Vertex shader
	VertexShader vs;

	// Fragment shader
	FragmentShader fs;

	// Program
	Program prog;

	// A vertex array object for the rendered cube
	VertexArray cube;

	// VBOs for the cube's vertex attributes
	Buffer verts, normals, tangents, texcoords;

	// The color and normalmap texture
	Texture colorTex, normalTex;
public:
	CubeExample(void)
	 : cube_instr(make_cube.Instructions())
	 , cube_indices(make_cube.Indices())
	{
		// Set the vertex shader source
		vs.Source(
			"#version 330\n"
			"uniform mat4 ProjectionMatrix, CameraMatrix, ModelMatrix;"
			"in vec4 Position;"
			"in vec3 Normal;"
			"in vec3 Tangent;"
			"in vec2 TexCoord;"
			"out vec3 vertLight;"
			"out vec2 vertTexCoord;"
			"out mat3 NormalMatrix;"
			"uniform vec3 lightPos;"
			"void main(void)"
			"{"
			"	vec3 fragNormal = ("
			"		ModelMatrix *"
			"		vec4(Normal, 0.0)"
			"	).xyz;"
			"	vec3 fragTangent = ("
			"		ModelMatrix *"
			"		vec4(Tangent, 0.0)"
			"	).xyz;"
			"	NormalMatrix[0] = fragTangent;"
			"	NormalMatrix[1] = cross(fragNormal, fragTangent);"
			"	NormalMatrix[2] = fragNormal;"
			"	vertLight = ("
			"		vec4(lightPos, 0.0)-"
			"		ModelMatrix * Position"
			"	).xyz;"
			"	vertTexCoord = TexCoord;"
			"	gl_Position = "
			"		ProjectionMatrix *"
			"		CameraMatrix *"
			"		ModelMatrix *"
			"		Position;"
			"}"
		);
		// compile it
		vs.Compile();

		// set the fragment shader source
		fs.Source(
			"#version 330\n"
			"uniform sampler2D ColorTex, NormalTex;"
			"in mat3 NormalMatrix;"
			"in vec3 vertLight;"
			"in vec2 vertTexCoord;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	float l = dot(vertLight, vertLight);"
			"	vec3 n = texture(NormalTex, vertTexCoord).xyz;"
			"	vec3 finalNormal = NormalMatrix * n;"
			"	float d = (l > 0.0) ? dot("
			"		normalize(vertLight), "
			"		finalNormal"
			"	) / l : 0.0;"
			"	float i = 0.2 + 4.5*d;"
			"	vec4 t  = texture(ColorTex, vertTexCoord);"
			"	fragColor = vec4(t.rgb*i, 1.0);"
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

		// bind the VAO for the cube
		cube.Bind();

		verts.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.Vertices(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(prog, "Position");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		normals.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.Normals(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(prog, "Normal");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		tangents.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.Tangents(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(prog, "Tangent");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		texcoords.Bind(Buffer::Target::Array);
		{
			std::vector<GLfloat> data;
			GLuint n_per_vertex = make_cube.TexCoordinates(data);
			Buffer::Data(Buffer::Target::Array, data);
			VertexAttribArray attr(prog, "TexCoord");
			attr.Setup(n_per_vertex, DataType::Float);
			attr.Enable();
		}

		// setup the textures
		{
			Texture::Active(0);
			Uniform(prog, "ColorTex").Set(0);
			auto bound_tex = Bind(colorTex, Texture::Target::_2D);
			bound_tex.Image2D(images::LoadTexture("wooden_crate"));
			bound_tex.GenerateMipmap();
			bound_tex.MinFilter(TextureMinFilter::LinearMipmapLinear);
			bound_tex.MagFilter(TextureMagFilter::Linear);
			bound_tex.WrapS(TextureWrap::Repeat);
			bound_tex.WrapT(TextureWrap::Repeat);
		}
		{
			Texture::Active(1);
			Uniform(prog, "NormalTex").Set(1);
			auto bound_tex = Bind(normalTex, Texture::Target::_2D);
			bound_tex.Image2D(
				images::NormalMap(
					images::LoadTexture("wooden_crate-hmap")
				)
			);
			bound_tex.GenerateMipmap();
			bound_tex.MinFilter(TextureMinFilter::LinearMipmapLinear);
			bound_tex.MagFilter(TextureMagFilter::Linear);
			bound_tex.WrapS(TextureWrap::Repeat);
			bound_tex.WrapT(TextureWrap::Repeat);
		}
		//
		gl.ClearColor(0.1f, 0.1f, 0.1f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::DepthTest);

		gl.Enable(Capability::CullFace);
		gl.FrontFace(make_cube.FaceWinding());
	}

	void Reshape(size_t width, size_t height)
	{
		gl.Viewport(width, height);
		prog.Use();
		Uniform(prog, "ProjectionMatrix").SetMatrix(
			CamMatrixf::Perspective(
				Degrees(24),
				double(width)/height,
				1, 100
			)
		);
	}

	void Render(double time)
	{
		gl.Clear().ColorBuffer().DepthBuffer();
		//
		auto lightAzimuth = FullCircles(time * -0.5);
		Uniform(prog, "lightPos").Set(
			Vec3f(
				Cos(lightAzimuth),
				1.0f,
				Sin(lightAzimuth)
			) * 2.0f
		);
		//
		Uniform(prog, "CameraMatrix").SetMatrix(
			CamMatrixf::Orbiting(
				Vec3f(),
				1.5f,
				Degrees(-45),
				Degrees(std::sin(time * 0.2) * 70)
			)
		);

		// set the model matrix
		Uniform(prog, "ModelMatrix").SetMatrix(
			ModelMatrixf::RotationY(FullCircles(time * 0.05))
		);

		cube.Bind();
		gl.CullFace(Face::Back);
		cube_instr.Draw(cube_indices);
	}

	bool Continue(double time)
	{
		return time < 30.0;
	}
};

std::unique_ptr<Example> makeExample(void)
{
	return std::unique_ptr<Example>(new CubeExample);
}

} // namespace oglplus

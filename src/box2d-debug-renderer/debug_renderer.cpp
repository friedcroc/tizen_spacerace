/* vim: set ai noet ts=4 sw=4 tw=115: */
//
// Copyright (c) 2014 Nikolay Zapolnov (zapolnov@gmail.com).
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
#include "debug_renderer.h"

static const char * g_VertexShaderCode = R"GLSL(
	uniform mat4 u_projection;
	uniform float u_pointSize;
	attribute vec2 a_position;
	void main()
	{
		gl_PointSize = u_pointSize;
		vec4 position = vec4(a_position, 0.0, 1.0);
		gl_Position = u_projection * position;
	}
)GLSL";

static const char * g_FragmentShaderCode = R"GLSL(
	#ifdef GL_ES
	precision mediump float;
	#endif
	uniform vec4 u_color;
	void main()
	{
		gl_FragColor = u_color;
	}
)GLSL";

DebugRenderer::DebugRenderer(const GL::ResourceManagerPtr & resManager)
	: m_ResourceManager(resManager),
	  m_Initialized(false)
{
}

DebugRenderer::~DebugRenderer()
{
}

void DebugRenderer::setupForRendering(const mat4 & projectionMatrix)
{
	GL::disable(GL::SCISSOR_TEST);
	GL::disable(GL::DEPTH_TEST);
	GL::disable(GL::STENCIL_TEST);
	GL::disable(GL::CULL_FACE);
	GL::disable(GL::POLYGON_OFFSET_FILL);
	GL::disable(GL::SAMPLE_ALPHA_TO_COVERAGE);
	GL::disable(GL::SAMPLE_COVERAGE);

	GL::enable(GL::BLEND);
	GL::blendFunc(GL::SRC_ALPHA, GL::ONE_MINUS_SRC_ALPHA);

	if (UNLIKELY(!m_Initialized))
	{
		m_Program = m_ResourceManager->createProgram();
		try
		{
			GL::ShaderPtr shader;

			std::clog << "Compiling vertex shader for the debug renderer." << std::endl;
			shader = m_ResourceManager->createShader(GL::VERTEX_SHADER);
			shader->initFromSource(g_VertexShaderCode);
			m_Program->attachShader(shader);

			std::clog << "Compiling fragment shader for the debug renderer." << std::endl;
			shader = m_ResourceManager->createShader(GL::FRAGMENT_SHADER);
			shader->initFromSource(g_FragmentShaderCode);
			m_Program->attachShader(shader);

			m_Program->link();
		}
		catch (...)
		{
			m_Program.reset();
			throw;
		}

		m_AttribPosition = GL::getAttribLocation(m_Program->handle(), "a_position");
		m_UniformProjection = GL::getUniformLocation(m_Program->handle(), "u_projection");
		m_UniformColor = GL::getUniformLocation(m_Program->handle(), "u_color");
		m_UniformPointSize = GL::getUniformLocation(m_Program->handle(), "u_pointSize");

		m_Initialized = true;
	}

	m_Program->use();

	GL::uniformMatrix4fv(m_UniformProjection, 1, GL::FALSE, &projectionMatrix[0]);
	GL::enableVertexAttribArray(m_AttribPosition);
}

void DebugRenderer::cleanupAfterRendering()
{
	GL::disableVertexAttribArray(m_AttribPosition);
	GL::useProgram(0);
}

void DebugRenderer::render(size_t mode, size_t numVertices, const b2Color & color, float ptSize) const
{
	GL::vertexAttribPointer(m_AttribPosition, 2, GL::FLOAT, GL::FALSE, 0, &m_Vertices[0]);

	if (mode & Triangles)
	{
		GL::uniform4f(m_UniformColor, color.r, color.g, color.b, 0.5f);
		GL::drawArrays(GL::TRIANGLE_FAN, 0, static_cast<GL::Sizei>(numVertices));
	}

	if (mode & (Lines | Points))
	{
		GL::uniform4f(m_UniformColor, color.r, color.g, color.b, 1.0f);

		if (mode & Lines)
			GL::drawArrays(GL::LINE_LOOP, 0, static_cast<GL::Sizei>(numVertices));

		if (mode & Points)
		{
			GL::uniform1f(m_UniformPointSize, ptSize);
			GL::drawArrays(GL::POINTS, 0, static_cast<GL::Sizei>(numVertices));
		}
	}
}

size_t DebugRenderer::rescaleVertices(const b2Vec2 * vertices, int vertexCount, float scale)
{
	size_t numVertices = static_cast<size_t>(vertexCount);

	size_t numFloats = numVertices * 2;
	if (UNLIKELY(m_Vertices.size() < numFloats))
		m_Vertices.resize(numFloats);

	size_t j = 0;
	for (int i = 0; i < vertexCount; i++)
	{
		m_Vertices[j++] = vertices[i].x * scale;
		m_Vertices[j++] = vertices[i].y * scale;
	}

	return numVertices;
}

size_t DebugRenderer::initCircleVertices(const b2Vec2 & center, float radius, float scale)
{
	const size_t NUM_VERTICES = 16;
	const float STEP = 2.0f * M_PI / NUM_VERTICES;

	size_t numFloats = NUM_VERTICES * 2;
	if (UNLIKELY(m_Vertices.size() < numFloats))
		m_Vertices.resize(numFloats);

	float angle = 0.0f;
	size_t j = 0;
	for (size_t i = 0; i < NUM_VERTICES; ++i)
	{
		b2Vec2 v = center + radius * b2Vec2(cosf(angle), sinf(angle));
		m_Vertices[j++] = v.x * scale;
		m_Vertices[j++] = v.y * scale;
		angle += STEP;
	}

	return NUM_VERTICES;
}

void DebugRenderer::drawCircle(const b2Vec2 & center, float32 radius, const b2Color & color)
{
	size_t n = initCircleVertices(center, radius);
	render(DebugRenderer::Lines, n, color);
}

void DebugRenderer::drawSolidCircle(const b2Vec2 & center, float32 radius, const b2Vec2 & axis,
	const b2Color & color)
{
	size_t n = initCircleVertices(center, radius);
	render(DebugRenderer::Lines | DebugRenderer::Triangles, n, color);
	drawSegment(center, center + radius * axis, color);
}

void DebugRenderer::drawSegment(const b2Vec2 & p1, const b2Vec2 & p2, const b2Color & color)
{
	b2Vec2 v[2] = { p1, p2 };
	size_t n = rescaleVertices(v, 2);
	render(DebugRenderer::Lines, n, color);
}

void DebugRenderer::drawPoint(const b2Vec2 & p, float32 size, const b2Color & color)
{
	size_t n = rescaleVertices(&p, 1);
	render(DebugRenderer::Points, n, color, size);
}

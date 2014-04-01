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
#ifndef __d03a602771e03784c4f8d10435dbf8c8__
#define __d03a602771e03784c4f8d10435dbf8c8__

#include "../gl/gl.h"
#include "../gl-wrappers/gl_resource_manager.h"
#include "../cxx-util/macros.h"
#include "../math/mat4.h"
#include "../box2d/Box2D/Box2D/Common/b2Draw.h"
#include <vector>

class DebugRenderer
{
public:
	enum Primitives
	{
		Points = 0x0001,
		Lines = 0x0002,
		Triangles = 0x0004
	};

	DebugRenderer(const GL::ResourceManagerPtr & resManager);
	~DebugRenderer();

	void setupForRendering(const mat4 & projectionMatrix);
	void cleanupAfterRendering();

	void render(size_t mode, size_t numVertices, const b2Color & color, float ptSize = 1.0f) const;

	size_t rescaleVertices(const b2Vec2 * vertices, int vertexCount, float scale = 1.0f);
	size_t initCircleVertices(const b2Vec2 & center, float radius, float scale = 1.0f);

	void drawCircle(const b2Vec2 & center, float32 radius, const b2Color & color);
	void drawSolidCircle(const b2Vec2 & center, float32 radius, const b2Vec2 & axis, const b2Color & color);
	void drawSegment(const b2Vec2 & p1, const b2Vec2 & p2, const b2Color & color);
	void drawPoint(const b2Vec2 & p, float32 size, const b2Color & color);

private:
	GL::ResourceManagerPtr m_ResourceManager;
	std::vector<GL::Float> m_Vertices;
	GL::ProgramPtr m_Program;
	int m_UniformProjection;
	int m_UniformColor;
	int m_UniformPointSize;
	int m_AttribPosition;
	bool m_Initialized;

	DebugRenderer(const DebugRenderer &) = delete;
	DebugRenderer & operator=(const DebugRenderer &) = delete;
};

#endif

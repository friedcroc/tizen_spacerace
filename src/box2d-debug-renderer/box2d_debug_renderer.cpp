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
/*
* Copyright (c) 2006-2007 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/
#include "box2d_debug_renderer.h"
#include <stdarg.h>

Box2DDebugRenderer::Box2DDebugRenderer(const GL::ResourceManagerPtr & resManager, unsigned flags)
	: DebugRenderer(resManager),
	  m_PixelsPerMeter(50.0f),
	  m_ProjectionMatrix(mat4::identity())
{
	SetFlags(flags);
}

Box2DDebugRenderer::~Box2DDebugRenderer()
{
}

void Box2DDebugRenderer::DrawPolygon(const b2Vec2 * vertices, int32 vertexCount, const b2Color & color)
{
	size_t n = rescaleVertices(vertices, vertexCount, m_PixelsPerMeter);
	DebugRenderer::render(DebugRenderer::Lines, n, color);
}

void Box2DDebugRenderer::DrawSolidPolygon(const b2Vec2 * vertices, int32 vertexCount, const b2Color & color)
{
	size_t n = rescaleVertices(vertices, vertexCount, m_PixelsPerMeter);
	DebugRenderer::render(DebugRenderer::Lines | DebugRenderer::Triangles, n, color);
}

void Box2DDebugRenderer::DrawCircle(const b2Vec2 & center, float32 radius, const b2Color & color)
{
	size_t n = initCircleVertices(center, radius, m_PixelsPerMeter);
	DebugRenderer::render(DebugRenderer::Lines, n, color);
}

void Box2DDebugRenderer::DrawSolidCircle(const b2Vec2 & center, float32 radius, const b2Vec2 & axis,
	const b2Color & color)
{
	size_t n = initCircleVertices(center, radius, m_PixelsPerMeter);
	DebugRenderer::render(DebugRenderer::Lines | DebugRenderer::Triangles, n, color);
	DrawSegment(center, center + radius * axis, color);
}

void Box2DDebugRenderer::DrawSegment(const b2Vec2 & p1, const b2Vec2 & p2, const b2Color & color)
{
	b2Vec2 v[2] = { p1, p2 };
	size_t n = rescaleVertices(v, 2, m_PixelsPerMeter);
	DebugRenderer::render(DebugRenderer::Lines, n, color);
}

void Box2DDebugRenderer::DrawTransform(const b2Transform & xf)
{
	const float32 AXIS_SCALE = 0.4f;
	DrawSegment(xf.p, xf.p + AXIS_SCALE * xf.q.GetXAxis(), b2Color(1, 0, 0));
	DrawSegment(xf.p, xf.p + AXIS_SCALE * xf.q.GetYAxis(), b2Color(0, 1, 0));
}

void Box2DDebugRenderer::render(b2World * world)
{
	DebugRenderer::setupForRendering(m_ProjectionMatrix);
	world->SetDebugDraw(this);
	world->DrawDebugData();
	world->SetDebugDraw(NULL);
	cleanupAfterRendering();
}

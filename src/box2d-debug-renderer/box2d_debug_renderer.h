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
#ifndef __0d981fab697a592b8e8b00c1b6fc54dc__
#define __0d981fab697a592b8e8b00c1b6fc54dc__

#include "debug_renderer.h"
#include "box2d/Box2D/Box2D/Box2D.h"
#include <vector>
#include <memory>

class Box2DDebugRenderer : public b2Draw, public DebugRenderer
{
public:
	Box2DDebugRenderer(const GL::ResourceManagerPtr & resManager, unsigned flags =
		b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);
	~Box2DDebugRenderer();

	inline const mat4 & projectionMatrix() const { return m_ProjectionMatrix; }
	inline void setProjectionMatrix(const mat4 & m) { m_ProjectionMatrix = m; }

	inline float pixelsPerMeter() const { return m_PixelsPerMeter; }
	inline void setPixelsPerMeter(float v) { m_PixelsPerMeter = v; }

	void DrawPolygon(const b2Vec2 * vertices, int32 vertexCount, const b2Color & color) override;
	void DrawSolidPolygon(const b2Vec2 * vertices, int32 vertexCount, const b2Color & color) override;
	void DrawCircle(const b2Vec2 & center, float32 radius, const b2Color & color) override;
	void DrawSolidCircle(const b2Vec2 & center, float32 r, const b2Vec2 & axis, const b2Color & color) override;
	void DrawSegment(const b2Vec2 & p1, const b2Vec2 & p2, const b2Color & color) override;
	void DrawTransform(const b2Transform & xf) override;

	inline void setupForRendering() { DebugRenderer::setupForRendering(m_ProjectionMatrix); }

	void render(b2World * world);
	inline void render(const std::unique_ptr<b2World> & world) { render(world.get()); }
	inline void render(const std::shared_ptr<b2World> & world) { render(world.get()); }

private:
	float m_PixelsPerMeter;
	mat4 m_ProjectionMatrix;

	Box2DDebugRenderer(const Box2DDebugRenderer &) = delete;
	Box2DDebugRenderer & operator=(const Box2DDebugRenderer &) = delete;
};

#endif

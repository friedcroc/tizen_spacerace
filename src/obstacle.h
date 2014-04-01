/* vim: set ai noet ts=4 sw=4 tw=115: */
//
// Copyright (c) 2014 FriedCroc Team (admin@friedcroc.com).
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
#ifndef __76de145bd248bd23bc8f089403f64a1b__
#define __76de145bd248bd23bc8f089403f64a1b__

#include "game_object.h"
#include "fixture_info.h"
#include "gl-wrappers/gl_texture.h"
#include "box2d/Box2D/Box2D/Box2D.h"
#include "tinyxml/tinyxml.h"

class Obstacle : public GameObject
{
public:
	Obstacle(b2World * world, TiXmlElement * element);
	~Obstacle();

	inline b2Body * body() const { return m_Body; }

	void runFrame(const mat4 & proj) override;

private:
	b2Body * m_Body;
	GL::TexturePtr m_Stone;
	float m_Scale;
	std::unique_ptr<FixtureInfo> m_FixtureInfo;

	Obstacle(const Obstacle &) = delete;
	Obstacle & operator=(const Obstacle &) = delete;
};

#endif

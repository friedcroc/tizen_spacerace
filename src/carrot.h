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
#ifndef __3e50780eb30297759891acb01f926a52__
#define __3e50780eb30297759891acb01f926a52__

#include "game_object.h"
#include "fixture_info.h"
#include "gl-wrappers/gl_texture.h"
#include "box2d/Box2D/Box2D/Box2D.h"
#include "tinyxml/tinyxml.h"
#include <memory>

class Carrot : public GameObject
{
public:
	Carrot(b2World * world, TiXmlElement * element);
	~Carrot();

	inline b2Body * body() const { return m_Body; }

	void runFrame(const mat4 & proj) override;

private:
	b2Body * m_Body;
	std::unique_ptr<FixtureInfo> m_FixtureInfo;
	GL::TexturePtr m_Carrot;

	Carrot(const Carrot &) = delete;
	Carrot & operator=(const Carrot &) = delete;
};

#endif

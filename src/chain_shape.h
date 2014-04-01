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
#ifndef __e344d0e870f1d054e042526d902dd3e5__
#define __e344d0e870f1d054e042526d902dd3e5__

#include "game_object.h"
#include "box2d/Box2D/Box2D/Box2D.h"
#include "tinyxml/tinyxml.h"
#include <vector>
#include <memory>

class ChainShape : public GameObject
{
public:
	ChainShape(b2World * world, TiXmlElement * element);
	~ChainShape();

	inline b2Body * body() const { return m_Body; }

	void runFrame(const mat4 & m) override;

private:
	std::vector<b2Vec2> m_Vertices;
	b2Body * m_Body;

	ChainShape(const ChainShape &) = delete;
	ChainShape & operator=(const ChainShape &) = delete;
};

#endif

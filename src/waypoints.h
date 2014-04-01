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
#ifndef __8c655b14cfbf1811ee2899d60c105a06__
#define __8c655b14cfbf1811ee2899d60c105a06__

#include "game_object.h"
#include "box2d/Box2D/Box2D/Box2D.h"
#include "tinyxml/tinyxml.h"
#include <vector>
#include <memory>

class Waypoints : public GameObject
{
public:
	class Iterator
	{
	public:
		Iterator(Waypoints * waypoints, const b2Vec2 & startPosition);
		inline ~Iterator() {}

		b2Vec2 getDirection(const b2Vec2 & curPosition);

		inline bool atEnd() const { return m_AtEnd; }

	private:
		Waypoints * m_Waypoints;
		size_t m_NextIndex;
		b2Vec2 m_Start;
		b2Vec2 m_StartDirection;
		b2Vec2 m_Direction;
		bool m_AtEnd;
	};

	Waypoints(b2World * world, TiXmlElement * element);
	~Waypoints();

	inline b2Body * body() const { return m_Body; }

private:
	std::vector<b2Vec2> m_Points;
	b2Body * m_Body;

	Waypoints(const Waypoints &) = delete;
	Waypoints & operator=(const Waypoints &) = delete;

	friend class Iterator;
};

#endif

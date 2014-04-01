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
#include "waypoints.h"
#include "util.h"
#include "game.h"
#include "gl-wrappers/gl_texture.h"
#include "cxx-util/fmt.h"
#include "math/util.h"
#include "math/common.h"
#include <vector>

/* Waypoints::Iterator */

Waypoints::Iterator::Iterator(Waypoints * waypoints, const b2Vec2 & startPosition)
	: m_Waypoints(waypoints),
	  m_NextIndex(0),
	  m_Start(startPosition),
	  m_StartDirection(0, 1),
	  m_Direction(0, 1),
	  m_AtEnd(false)
{
	if (m_Waypoints->m_Points.size() == 0)
		m_AtEnd = true;
	else
	{
		m_Direction = (m_Waypoints->m_Points[0] - startPosition);
		if (m_Direction.x == 0.0f && m_Direction.y == 0.0f)
		{
			if (m_Waypoints->m_Points.size() == 1)
			{
				m_AtEnd = true;
				m_Direction = b2Vec2(0, 1);
			}
			else
			{
				m_NextIndex = 1;
				m_Direction = m_Waypoints->m_Points[1] - m_Waypoints->m_Points[0];
			}
		}
		m_Direction.Normalize();
		m_StartDirection = m_Direction;
	}
}

b2Vec2 Waypoints::Iterator::getDirection(const b2Vec2 & curPosition)
{
	if (m_AtEnd)
		return m_Direction;

	vec2 pt(curPosition.x, curPosition.y);
	const b2Vec2 & start = m_Start;
	const b2Vec2 & end = m_Waypoints->m_Points[m_NextIndex];
	float step = pointPositionOnSegment(vec2(start.x, start.y), vec2(end.x, end.y), pt);
	if (step < 0.0f)
		step = 0.0f;
	else if (step > 1.0f)
	{
		step = 0.0f;
		m_StartDirection = m_Direction;
		m_Start = m_Waypoints->m_Points[m_NextIndex++];
		if (m_NextIndex >= m_Waypoints->m_Points.size())
		{
			m_AtEnd = true;
			return m_Direction;
		}
	}

	b2Vec2 endDirection = m_Waypoints->m_Points[m_NextIndex] - m_Start;
	endDirection.Normalize();

//	b2Vec2 direction = endDirection - m_StartDirection;
//	direction *= step;
//	direction += m_StartDirection;
//	direction.Normalize();

	b2Vec2 targetDirection = m_Waypoints->m_Points[m_NextIndex] - curPosition;
	targetDirection.Normalize();

	b2Vec2 dir = (targetDirection + endDirection);
	dir *= 0.5f;
	dir.Normalize();
	m_Direction = dir;

	return m_Direction;
}


/* Waypoints */

Waypoints::Waypoints(b2World * world, TiXmlElement * element)
{
	TiXmlElement * vert = element->FirstChildElement("vertices");
	if (!vert)
		throw std::runtime_error("there is no element 'vertices' in the waypoints list.");

	for (TiXmlElement * e = vert->FirstChildElement("item"); e; e = e->NextSiblingElement("item"))
	{
		const char * text = e->GetText();
		if (!text)
			throw std::runtime_error("invalid item in the waypoints list.");

		m_Points.push_back(parseVec2(text));
	}

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	m_Body = world->CreateBody(&bodyDef);

	b2ChainShape shape;
	shape.CreateChain(m_Points.data(), static_cast<int32>(m_Points.size()));

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.friction = 0.5;
	fixtureDef.restitution = 0.3;
	fixtureDef.isSensor = true;
	m_Body->CreateFixture(&fixtureDef);
}

Waypoints::~Waypoints()
{
}

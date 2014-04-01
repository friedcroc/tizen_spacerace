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
#include "obstacle.h"
#include "game.h"
#include "util.h"
#include "fixture_info.h"
#include "math/common.h"
#include <stdexcept>

Obstacle::Obstacle(b2World * world, TiXmlElement * element)
	: m_FixtureInfo(new FixtureInfo)
{
	m_FixtureInfo->kind = FIXT_OBSTACLE;
	m_Stone = Game::instance()->resourceManager()->getTexture("res/stone.png");

	// Translation

	TiXmlElement * e = element->FirstChildElement("translation");
	if (!e)
		throw std::runtime_error("missing 'translation' in the 'Obstacle' element.");

	const char * translationText = e->GetText();
	if (!translationText)
		throw std::runtime_error("invalid value of 'translation' in the 'Obstacle' element.");

	b2Vec2 pos = parseVec2(translationText);

	// Scale

	e = element->FirstChildElement("scale");
	if (!e)
		throw std::runtime_error("missing 'scale' in the 'Obstacle' element.");

	const char * scaleText = e->GetText();
	if (!scaleText)
		throw std::runtime_error("invalid value of 'scale' in the 'Obstacle' element.");

	m_Scale = static_cast<float>(parseDouble(scaleText)) * 0.3f;

	// Create physical body

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = pos;
	bodyDef.linearDamping = 0.9f;
	bodyDef.angularDamping = 7.0f;
	bodyDef.bullet = true;
	m_Body = world->CreateBody(&bodyDef);

	b2CircleShape shape;
	shape.m_radius = m_Scale * 3.0f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.userData = m_FixtureInfo.get();
	fixtureDef.friction = 0.3;
	fixtureDef.density = 0.1;
	m_Body->CreateFixture(&fixtureDef);
}

Obstacle::~Obstacle()
{
}

void Obstacle::runFrame(const mat4 & proj)
{
	b2Vec2 pos = m_Body->GetWorldCenter();
	mat4 mat = proj * mat4::translation(pos.x, pos.y, 0.0f);
	float scale = m_Scale * 2.0f * (1.0f / 0.3f);
	render(mat, m_Stone, scale, scale);
}

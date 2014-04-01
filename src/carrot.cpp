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
#include "carrot.h"
#include "game.h"
#include "util.h"
#include "math/common.h"
#include <stdexcept>

Carrot::Carrot(b2World * world, TiXmlElement * element)
	: m_FixtureInfo(new FixtureInfo)
{
	m_FixtureInfo->kind = FIXT_CARROT;
	m_FixtureInfo->carrot = this;

	m_Carrot = Game::instance()->resourceManager()->getTexture("res/carrot.png");

	// Translation

	TiXmlElement * e = element->FirstChildElement("translation");
	if (!e)
		throw std::runtime_error("missing 'translation' in the 'Carrot' element.");

	const char * translationText = e->GetText();
	if (!translationText)
		throw std::runtime_error("invalid value of 'translation' in the 'Carrot' element.");

	b2Vec2 pos = parseVec2(translationText);

	// Create physical body

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position = pos;
	m_Body = world->CreateBody(&bodyDef);

	b2CircleShape shape;
	shape.m_radius = 2.0f;

	b2FixtureDef fixtureDef;
	fixtureDef.userData = m_FixtureInfo.get();
	fixtureDef.shape = &shape;
	fixtureDef.isSensor = true;
	m_Body->CreateFixture(&fixtureDef);
}

Carrot::~Carrot()
{
}

void Carrot::runFrame(const mat4 & proj)
{
	if (!m_Body->IsActive())
		return;

	b2Vec2 pos = m_Body->GetWorldCenter();
	mat4 mat = proj * mat4::translation(pos.x, pos.y, 0.0f);
	float scale = (1.0f / 0.3f);
	render(mat, m_Carrot, scale, scale);
}

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
#include "car.h"
#include "fixture_info.h"
#include "game.h"
#include "util.h"
#include "math/common.h"
#include "math/vec2.h"
#include <stdexcept>

Car::Car(b2World * world, TiXmlElement * element, const CarParameters & params)
	: m_WayDirection(0, 0),
	  m_Waypoints(nullptr),
	  m_FixtureInfo(new FixtureInfo),
	  m_TextureIndex(0),
	  m_TextureChangeTime(0),
	  m_Width(1.5f * 3),
	  m_Height(2.5f * 3),
	  m_Left(false),
	  m_Right(false)
{
	m_FixtureInfo->kind = FIXT_PLAYER;

	m_Textures[0] = Game::instance()->resourceManager()->getTexture("res/ship1.png");
	m_Textures[1] = Game::instance()->resourceManager()->getTexture("res/ship2.png");

	TiXmlElement * e = element->FirstChildElement("translation");
	if (!e)
		throw std::runtime_error("missing 'translation' in the 'Ship' element.");

	const char * translationText = e->GetText();
	if (!translationText)
		throw std::runtime_error("invalid value of 'translation' in the 'Ship' element.");

	b2Vec2 pos = parseVec2(translationText);

	float halfWidth = m_Width * 0.5f;
	float halfHeight = m_Height * 0.5f;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = pos;
	bodyDef.linearDamping = params.linearDamping;
	bodyDef.angularDamping = params.angularDamping;
	bodyDef.bullet = true;
	m_Body = world->CreateBody(&bodyDef);

	static const b2Vec2 v[] = {
		b2Vec2(-halfWidth, -halfHeight),
		b2Vec2( halfWidth, -halfHeight),
		b2Vec2( halfWidth,  halfHeight),
		b2Vec2(0.0f,       -halfHeight * 1.5f),
		b2Vec2(-halfWidth,  halfHeight)
	};

	b2PolygonShape shape;
//	shape.SetAsBox(halfWidth, halfHeight);
	shape.Set(v, sizeof(v) / sizeof(v[0]));
//	b2CircleShape shape;
//	shape.m_radius = m_Width;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.userData = m_FixtureInfo.get();
	fixtureDef.friction = params.friction;
	fixtureDef.restitution = params.restitution;
	fixtureDef.density = params.density;
	m_Body->CreateFixture(&fixtureDef);

	m_Wheels.emplace_back(new CarWheel(this, b2Vec2(-halfWidth, -halfHeight), true, true));
	m_Wheels.emplace_back(new CarWheel(this, b2Vec2( halfWidth, -halfHeight), true, true));
	m_Wheels.emplace_back(new CarWheel(this, b2Vec2(-halfWidth,  halfHeight), false, false));
	m_Wheels.emplace_back(new CarWheel(this, b2Vec2( halfWidth,  halfHeight), false, false));
}

Car::~Car()
{
}

void Car::setWaypoints(Waypoints * waypoints)
{
	m_Waypoints = waypoints;
	if (!m_Waypoints)
		m_WaypointsIterator.reset();
	else
		m_WaypointsIterator.reset(new Waypoints::Iterator(waypoints, m_Body->GetWorldCenter()));
}

void Car::runFrame(const mat4 & proj)
{
//	for (const std::unique_ptr<CarWheel> & it : m_Wheels)
//		it->addFriction();

	float carAngle = m_Body->GetAngle();
	float steerAngle = 0.0f;

	if (m_Left)
		steerAngle -= deg2rad(m_Params.maxRotationAngle);
	if (m_Right)
		steerAngle += deg2rad(m_Params.maxRotationAngle);

	m_Wheels[0]->body()->SetTransform(m_Wheels[0]->body()->GetTransform().p, carAngle + steerAngle);
	m_Wheels[1]->body()->SetTransform(m_Wheels[1]->body()->GetTransform().p, carAngle + steerAngle);

	while (carAngle < 0.0f)
		carAngle += 2.0f * M_PI;
	while (carAngle > 2.0f * M_PI)
		carAngle -= 2.0f * M_PI;

	if (m_WaypointsIterator.get())
		m_WayDirection = m_WaypointsIterator->getDirection(m_Body->GetWorldCenter());

	float torque = 0.0f;
	carAngle -= radiansBetween(vec2(0, -1), vec2(m_WayDirection.x, m_WayDirection.y)) + steerAngle;
	if (fabs(carAngle) > 0.01f)
	{
		if (carAngle > M_PI)
			torque = (2.0f * M_PI - carAngle);
		else if (carAngle < M_PI)
			torque = -carAngle;
		torque *= 150.0f;
		m_Body->ApplyTorque(torque, true);
	}

	b2Vec2 carSpeed1, carSpeed2;
//	carSpeed1.y = -cosf(-carAngle) * 10;
//	carSpeed1.x = -sinf(-carAngle) * 10;
//	m_Body->ApplyForce(carSpeed1, m_Body->GetWorldCenter(), true);
	carSpeed2.y = -cosf(-m_Body->GetAngle()) * 50;
	carSpeed2.x = -sinf(-m_Body->GetAngle()) * 50;
//	m_Wheels[0]->body()->SetLinearVelocity(carSpeed);
//	m_Wheels[1]->body()->SetLinearVelocity(carSpeed);
	m_Wheels[0]->body()->ApplyForce(carSpeed2, m_Wheels[0]->body()->GetWorldCenter(), true);
	m_Wheels[1]->body()->ApplyForce(carSpeed2, m_Wheels[1]->body()->GetWorldCenter(), true);

	if (m_Left || m_Right)
	{
		b2Vec2 contrForce = m_WayDirection;
		contrForce.Normalize();
		contrForce *= -20;
		m_Body->ApplyForce(contrForce, m_Body->GetTransform().p, true);
	}

	++m_TextureChangeTime;
	if (m_TextureChangeTime >= 3)
	{
		m_TextureChangeTime = 0;
		m_TextureIndex ^= 1;
	}

	b2Vec2 pos = m_Body->GetWorldCenter();
	mat4 mat = proj * mat4::translation(pos.x, pos.y, 0.0f);
	mat = mat * mat4::rotationZ(-m_Body->GetAngle());
	render(mat, m_Textures[m_TextureIndex], m_Width * 1.3f, m_Height * 1.3f);
}

void Car::onKeyPress(Sys::KeyCode key)
{
	switch (key)
	{
	case Sys::Key_Left: m_Left = true; break;
	case Sys::Key_Right: m_Right = true; break;
	default: return;
	}
}

void Car::onKeyRelease(Sys::KeyCode key)
{
	switch (key)
	{
	case Sys::Key_Left: m_Left = false; break;
	case Sys::Key_Right: m_Right = false; break;
	default: return;
	}
}

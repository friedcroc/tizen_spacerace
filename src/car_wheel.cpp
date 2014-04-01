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
#include "car_wheel.h"
#include "car.h"
#include "math/common.h"

CarWheel::CarWheel(Car * car, const b2Vec2 & pos, bool isFront, bool rotating)
	: m_Car(car),
	  m_Front(isFront)
{
	b2World * world = car->body()->GetWorld();
	float halfWidth = 0.2;
	float halfHeight = 0.5;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.linearDamping = car->parameters().linearDamping;
	bodyDef.angularDamping = car->parameters().angularDamping;
	bodyDef.position = car->body()->GetWorldCenter() + pos;
	m_Body = world->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(halfWidth, halfHeight);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.friction = car->parameters().friction;
	fixtureDef.restitution = car->parameters().restitution;
	fixtureDef.density = car->parameters().density;
	fixtureDef.isSensor = true;
	m_Body->CreateFixture(&fixtureDef);

	b2RevoluteJointDef jointDef;
	jointDef.bodyA = m_Body;
	jointDef.bodyB = car->body();
	jointDef.localAnchorB = pos;
	jointDef.collideConnected = false;
	jointDef.enableLimit = true;
	jointDef.enableMotor = rotating;
	jointDef.lowerAngle = (rotating ? -deg2rad(car->parameters().maxRotationAngle) : 0);
	jointDef.upperAngle = (rotating ?  deg2rad(car->parameters().maxRotationAngle) : 0);
	world->CreateJoint(&jointDef);
}

CarWheel::~CarWheel()
{
}

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
#include "math/mat3.h"
#include "math/mat4.h"
#include "cxx-util/fmt.h"
#include "tinyxml/tinyxml.h"
#include "gl-wrappers/gl_vertex_attrib_pointer.h"
#include "gl-wrappers/gl_program_binder.h"
#include "gl-wrappers/gl_texture_binder.h"
#include "menu.h"
#include "game.h"
#include "chain_shape.h"
#include "game_level.h"
#include "obstacle.h"
#include "util.h"
#include "fixture_info.h"
#include "carrot.h"
#include <locale.h>

GameLevel::GameLevel()
	: m_World(new b2World(b2Vec2(0, 0)))
{
	m_World->SetContactListener(this);
	initFromXml(Resource::Loader::standard().loadResource("level.xml"));
}

GameLevel::~GameLevel()
{
}

void GameLevel::initFromXml(const std::string & xml)
{
	CarParameters carParams;
	TiXmlDocument doc;

	setlocale(LC_NUMERIC, "C");

	if (!doc.LoadBuffer(xml.data(), xml.length()))
	{
		throw std::runtime_error(fmt() << "unable to parse XML: at line " << doc.ErrorRow() << ", "
			<< " column " << doc.ErrorCol() << ": " << doc.ErrorDesc());
	}

	for (TiXmlElement * e = doc.RootElement()->FirstChildElement(); e; e = e->NextSiblingElement())
	{
		if (e->ValueStr() == "ChainShape")
		{
			std::unique_ptr<GameObject> object(new ChainShape(m_World.get(), e));
			m_GameObjects.push_back(std::move(object));
		}
		else if (e->ValueStr() == "Obstacle")
		{
			std::unique_ptr<GameObject> object(new Obstacle(m_World.get(), e));
			m_GameObjects.push_back(std::move(object));
		}
		else if (e->ValueStr() == "CollectableItem")
		{
			std::unique_ptr<GameObject> object(new Carrot(m_World.get(), e));
			m_GameObjects.push_back(std::move(object));
		}
		else if (e->ValueStr() == "Waypoints")
			m_Waypoints.reset(new Waypoints(m_World.get(), e));
		else if (e->ValueStr() == "Ship")
		{
			m_PlayerCar = new Car(m_World.get(), e, carParams);
			m_Cars.emplace_back(m_PlayerCar);
		}
	}

	m_PlayerCar->setWaypoints(m_Waypoints.get());
}

void GameLevel::runFrame()
{
	if (m_PlayerCar && m_PlayerCar->atFinish())
	{
		Game::instance()->setLevel(std::unique_ptr<Level>(new Menu));
		return;
	}

	// Kill collected carrots

	while (m_CollectedCarrots.size() > 0)
	{
		Carrot * carrot = m_CollectedCarrots.back();
		m_CollectedCarrots.pop_back();
		carrot->body()->SetActive(false);
	}

	// Run physics

	m_World->Step(1.0f / 60.0f, 6, 2);

	// Get player position

	b2Vec2 playerPos = m_PlayerCar->body()->GetTransform().p;
	playerPos *= 50.0f;

	// Render background

	mat4 projectionMatrix = mat4::ortho(0, 720, 1280, 0, -100, 100);
	renderBack(projectionMatrix, playerPos.x * 0.01f, playerPos.y * 0.01f);

	// Calculate projection matrix

	projectionMatrix = projectionMatrix * mat4::scaling(0.3f, 0.3f, 1.0f);
	projectionMatrix = projectionMatrix * mat4::translation(
		(720.0 / 2.0) / 0.3f - playerPos.x,
		(1280.0 / 2.0) / 0.3f - playerPos.y, 0);

	// Render game objects

	mat4 projMatrix = projectionMatrix * mat4::scaling(50.0f, 50.0f, 1.0f);
	for (const std::unique_ptr<GameObject> & it : m_GameObjects)
		it->runFrame(projMatrix);

	// Render cars

	for (const std::unique_ptr<Car> & it : m_Cars)
		it->runFrame(projMatrix);

	// Debug rendering

  #ifndef NDEBUG

	Game::instance()->debugRenderer().setProjectionMatrix(projectionMatrix);
	Game::instance()->debugRenderer().render(m_World);

	b2Vec2 center = m_PlayerCar->body()->GetWorldCenter();
	b2Vec2 dir = m_PlayerCar->wayDirection();
	dir *= 10.0;
	Game::instance()->debugRenderer().setupForRendering();
	Game::instance()->debugRenderer().DrawSegment(center, center + dir, b2Color(255,255,255));
	Game::instance()->debugRenderer().cleanupAfterRendering();

  #endif
}

void GameLevel::onKeyPress(Sys::KeyCode key)
{
	m_PlayerCar->onKeyPress(key);
}

void GameLevel::onKeyRelease(Sys::KeyCode key)
{
	m_PlayerCar->onKeyRelease(key);
}

void GameLevel::BeginContact(b2Contact * contact)
{
	b2Fixture * f1 = contact->GetFixtureA();
	b2Fixture * f2 = contact->GetFixtureB();

	FixtureInfo * info1 = reinterpret_cast<FixtureInfo *>(f1->GetUserData());
	FixtureInfo * info2 = reinterpret_cast<FixtureInfo *>(f2->GetUserData());

	if (!info1 || !info2)
		return;

	FixtureInfo * target;
	if (info1->kind == FIXT_PLAYER)
		target = info2;
	else if (info2->kind == FIXT_PLAYER)
		target = info1;
	else
		return;

	switch (target->kind)
	{
	default: return;
	case FIXT_OBSTACLE: printf("obstacle!\n"); return;
	case FIXT_CARROT: m_CollectedCarrots.push_back(target->carrot); return;
	}
}

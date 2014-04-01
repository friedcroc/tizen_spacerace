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
#ifndef __7ade47888f0d7d16b89e2bcb6c4d1d05__
#define __7ade47888f0d7d16b89e2bcb6c4d1d05__

#include "game_object.h"
#include "car.h"
#include "waypoints.h"
#include "level.h"
#include "gl-wrappers/gl_texture.h"
#include "game-main/key_code.h"
#include "box2d/Box2D/Box2D/Box2D.h"
#include <memory>
#include <vector>

class Carrot;

class GameLevel : public Level, public b2ContactListener
{
public:
	GameLevel();
	~GameLevel();

	inline b2World * world() const { return m_World.get(); }

	void initFromXml(const std::string & xml);

	void runFrame() override;

	void onKeyPress(Sys::KeyCode key) override;
	void onKeyRelease(Sys::KeyCode key) override;

private:
	std::unique_ptr<Waypoints> m_Waypoints;
	std::unique_ptr<b2World> m_World;
	std::vector<std::unique_ptr<GameObject>> m_GameObjects;
	std::vector<std::unique_ptr<Car>> m_Cars;
	Car * m_PlayerCar;
	std::vector<Carrot *> m_CollectedCarrots;

	void BeginContact(b2Contact * contact);

	GameLevel(const GameLevel &) = delete;
	GameLevel & operator=(const GameLevel &) = delete;
};

#endif

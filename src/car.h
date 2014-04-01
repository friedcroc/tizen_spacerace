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
#ifndef __d149337d1114d793c5d2fc18a8521e96__
#define __d149337d1114d793c5d2fc18a8521e96__

#include "game_object.h"
#include "waypoints.h"
#include "car_parameters.h"
#include "car_wheel.h"
#include "fixture_info.h"
#include "gl-wrappers/gl_texture.h"
#include "game-main/key_code.h"
#include "box2d/Box2D/Box2D/Box2D.h"
#include "tinyxml/tinyxml.h"
#include <vector>
#include <memory>

class Car : public GameObject
{
public:
	Car(b2World * world, TiXmlElement * element, const CarParameters & params);
	~Car();

	inline const CarParameters & parameters() const { return m_Params; }
	inline b2Body * body() const { return m_Body; }

	void setWaypoints(Waypoints * waypoints);
	inline bool atFinish() const { return m_WaypointsIterator.get() && m_WaypointsIterator->atEnd(); }
	inline const b2Vec2 & wayDirection() const { return m_WayDirection; }

	void runFrame(const mat4 & proj) override;

	void onKeyPress(Sys::KeyCode key);
	void onKeyRelease(Sys::KeyCode key);

private:
	CarParameters m_Params;
	b2Body * m_Body;
	b2Vec2 m_WayDirection;
	Waypoints * m_Waypoints;
	std::unique_ptr<FixtureInfo> m_FixtureInfo;
	std::unique_ptr<Waypoints::Iterator> m_WaypointsIterator;
	std::vector<std::unique_ptr<CarWheel>> m_Wheels;
	GL::TexturePtr m_Textures[2];
	size_t m_TextureIndex;
	size_t m_TextureChangeTime;
	float m_Width;
	float m_Height;
	bool m_Left;
	bool m_Right;

	Car(const Car &) = delete;
	Car & operator=(const Car &) = delete;
};

#endif

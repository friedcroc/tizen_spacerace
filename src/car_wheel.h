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
#ifndef __b7afb13b53c2c8483b98614574878c9b__
#define __b7afb13b53c2c8483b98614574878c9b__

#include "box2d/Box2D/Box2D/Box2D.h"
#include <memory>

class Car;

class CarWheel
{
public:
	CarWheel(Car * car, const b2Vec2 & pos, bool isFront, bool rotating);
	~CarWheel();

	inline b2Body * body() const { return m_Body; }

private:
	Car * m_Car;
	b2Body * m_Body;
	bool m_Front;

	CarWheel(const CarWheel &) = delete;
	CarWheel & operator=(const CarWheel &) = delete;
};

#endif

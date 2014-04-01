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
#ifndef __36aa1777339b71f3843fa3c671b788cd__
#define __36aa1777339b71f3843fa3c671b788cd__

#include "game_object.h"
#include "car.h"
#include "waypoints.h"
#include "gl-wrappers/gl_texture.h"
#include "game-main/key_code.h"
#include "box2d/Box2D/Box2D/Box2D.h"
#include "math/mat4.h"
#include <memory>
#include <vector>

class Level
{
public:
	Level();
	virtual ~Level();

	virtual void runFrame() {}

	virtual void onKeyPress(Sys::KeyCode key) {}
	virtual void onKeyRelease(Sys::KeyCode key) {}

protected:
	void renderBack(const mat4 & projectionMatrix, float x = 0.0f, float y = 0.0f);

private:
	GL::TexturePtr m_BackTexture;

	Level(const Level &) = delete;
	Level & operator=(const Level &) = delete;
};

#endif

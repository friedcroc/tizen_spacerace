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
#ifndef __cace9fbe00abd40b547ad27de2130c54__
#define __cace9fbe00abd40b547ad27de2130c54__

#include "game-main/game_instance.h"
#include "box2d-debug-renderer/box2d_debug_renderer.h"
#include <memory>
#include "level.h"

class Game : public GameInstance
{
public:
	inline Game() {}
	inline ~Game() {}

	static inline Game * instance() { return static_cast<Game *>(GameInstance::instance()); }

	inline Box2DDebugRenderer & debugRenderer() const { return *m_DebugRenderer; }

	inline void setLevel(std::unique_ptr<Level> && level) { m_Level = std::move(level); }
	inline Level * currentLevel() const { return m_Level.get(); }

	void init() override;
	void cleanup() override;
	void runFrame() override;

	void configureOpenGL(OpenGLInitOptions & options) override;

	void onKeyPress(Sys::KeyCode key) override;
	void onKeyRelease(Sys::KeyCode key) override;

private:
	std::unique_ptr<Box2DDebugRenderer> m_DebugRenderer;
	std::unique_ptr<Level> m_Level;

	Game(const Game &) = delete;
	Game & operator=(const Game &) = delete;
};

#endif

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
#include "game.h"
#include "menu.h"
#include "game_level.h"
#include "resources/resource_loader.h"
#include <cstdio>

GAME_MAIN_CLASS(Game)

void Game::init()
{
	m_DebugRenderer.reset(new Box2DDebugRenderer(resourceManager()));
	m_Level.reset(new Menu);
}

void Game::cleanup()
{
	m_Level.reset();
	m_DebugRenderer.reset();
}

void Game::runFrame()
{
	GL::clearColor(0, 0, 0, 1);
	GL::clear(GL::COLOR_BUFFER_BIT | GL::DEPTH_BUFFER_BIT);

	if (m_Level)
		m_Level->runFrame();
}

void Game::configureOpenGL(OpenGLInitOptions & options)
{
	options.desiredWidth = 720;
	options.desiredHeight = 1280;
	options.depthBits = 16;
}

void Game::onKeyPress(Sys::KeyCode key)
{
	if (m_Level)
		m_Level->onKeyPress(key);
}

void Game::onKeyRelease(Sys::KeyCode key)
{
	if (m_Level)
		m_Level->onKeyRelease(key);
}

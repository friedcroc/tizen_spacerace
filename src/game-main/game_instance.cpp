/* vim: set ai noet ts=4 sw=4 tw=115: */
//
// Copyright (c) 2014 Nikolay Zapolnov (zapolnov@gmail.com).
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
#include "game_instance.h"
#include <cassert>
#include <stdexcept>

extern "C" void * c9737b5fd();

GameInstance::GameInstance() noexcept
	: m_ResourceManagerDestroyed(false),
	  m_ViewportWidth(0),
	  m_ViewportHeight(0)
{
}

GameInstance::~GameInstance() noexcept
{
}

GameInstance * GameInstance::instance() noexcept
{
	return reinterpret_cast<GameInstance *>(c9737b5fd());
}

const GL::ResourceManagerPtr & GameInstance::resourceManager() const
{
	if (LIKELY(m_ResourceManager))
		return m_ResourceManager;
	if (UNLIKELY(m_ResourceManagerDestroyed))
		throw std::runtime_error("resource manager has been destroyed.");
	m_ResourceManager = std::make_shared<GL::ResourceManager>();
	return m_ResourceManager;
}

void GameInstance::cleanup_()
{
	m_ResourceManagerDestroyed = true;
	if (m_ResourceManager)
	{
		m_ResourceManager->destroyAllResources();
		m_ResourceManager.reset();
	}
	cleanup();
}

void GameInstance::runFrame_()
{
	if (m_ResourceManager)
		m_ResourceManager->collectGarbage();
	runFrame();
}

void GameInstance::configureOpenGL(OpenGLInitOptions & options)
{
	(void)options;
}

void GameInstance::onMouseButtonDown(int x, int y, Sys::MouseButton button)
{
	(void)x;
	(void)y;
	(void)button;
}

void GameInstance::onMouseButtonUp(int x, int y, Sys::MouseButton button)
{
	(void)x;
	(void)y;
	(void)button;
}

void GameInstance::onMouseMove(int x, int y)
{
	(void)x;
	(void)y;
}

void GameInstance::onKeyPress(Sys::KeyCode key)
{
	(void)key;
}

void GameInstance::onKeyRelease(Sys::KeyCode key)
{
	(void)key;
}

void GameInstance::onCharInput(uint16_t ch)
{
	(void)ch;
}

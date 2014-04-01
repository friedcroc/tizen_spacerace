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
#include "opengl_renderer.h"
#include "../game_instance.h"
#include <FBase.h>

TizenPort::OpenGLRenderer::OpenGLRenderer()
	: m_ControlWidth(0),
	  m_ControlHeight(0)
{
}

TizenPort::OpenGLRenderer::~OpenGLRenderer()
{
}

bool TizenPort::OpenGLRenderer::InitializeGl()
{
	try
	{
		GameInstance::instance()->init();
	}
	catch (const std::exception & e)
	{
		AppLogException(e.what());
		return false;
	}

	return true;
}

bool TizenPort::OpenGLRenderer::TerminateGl()
{
	try
	{
		GameInstance::instance()->cleanup_();
	}
	catch (const std::exception & e)
	{
		AppLogException(e.what());
		return false;
	}

	return true;
}

bool TizenPort::OpenGLRenderer::Draw()
{
	try
	{
		GameInstance::instance()->setViewportSize_(m_ControlWidth, m_ControlHeight);
		GameInstance::instance()->runFrame_();
	}
	catch (const std::exception & e)
	{
		AppLogException(e.what());
		return false;
	}

	return true;
}

bool TizenPort::OpenGLRenderer::Pause()
{
	return true;
}

bool TizenPort::OpenGLRenderer::Resume()
{
	return true;
}

int TizenPort::OpenGLRenderer::GetTargetControlWidth()
{
	return m_ControlWidth;
}

int TizenPort::OpenGLRenderer::GetTargetControlHeight()
{
	return m_ControlHeight;
}

void TizenPort::OpenGLRenderer::SetTargetControlWidth(int width)
{
	m_ControlWidth = width;
}

void TizenPort::OpenGLRenderer::SetTargetControlHeight(int height)
{
	m_ControlHeight = height;
}

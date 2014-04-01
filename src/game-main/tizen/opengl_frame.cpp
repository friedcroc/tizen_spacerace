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
#include "opengl_frame.h"
#include "../game_instance.h"
#include <FApp.h>

// FIXME FIXME FIXME
static bool left = false, right = false, middle = false;
static void keyPressRelease(int x, int y, int width, bool press)
{
	bool newLeft = false, newRight = false, newMiddle = false;

	if (press)
	{
		int x1 = width / 3;
		int x2 = 2 * x1;

		if (x < x1)
			newLeft = true;
		else if (x > x2)
			newRight = true;
		else
			newMiddle = true;
	}

	if (newLeft != left)
	{
		left = newLeft;
		if (newLeft)
			GameInstance::instance()->onKeyPress(Sys::Key_Left);
		else
			GameInstance::instance()->onKeyRelease(Sys::Key_Left);
	}

	if (newRight != right)
	{
		right = newRight;
		if (newRight)
			GameInstance::instance()->onKeyPress(Sys::Key_Right);
		else
			GameInstance::instance()->onKeyRelease(Sys::Key_Right);
	}

	if (newMiddle != middle)
	{
		middle = newMiddle;
		if (newMiddle)
			GameInstance::instance()->onKeyPress(Sys::Key_Enter);
		else
			GameInstance::instance()->onKeyRelease(Sys::Key_Enter);
	}
}

result TizenPort::OpenGLFrame::OnInitializing()
{
	return E_SUCCESS;
}

result TizenPort::OpenGLFrame::OnTerminating()
{
	return E_SUCCESS;
}

void TizenPort::OpenGLFrame::OnFrameActivated(const Tizen::Ui::Controls::Frame & source)
{
	result r = Tizen::System::PowerManager::KeepScreenOnState(true, false);
	TryLog(!IsFailed(r), "unable to enable the 'KeepScreenOn' state.");
}

void TizenPort::OpenGLFrame::OnFrameTerminating(const Tizen::Ui::Controls::Frame & source)
{
}

void TizenPort::OpenGLFrame::OnTouchCanceled(const Control & src, const Point & pos, const TouchEventInfo & info)
{
}

void TizenPort::OpenGLFrame::OnTouchFocusIn(const Control & src, const Point & pos, const TouchEventInfo & info)
{
}

void TizenPort::OpenGLFrame::OnTouchFocusOut(const Control & src, const Point & pos, const TouchEventInfo & info)
{
}

void TizenPort::OpenGLFrame::OnTouchMoved(const Control & src, const Point & pos, const TouchEventInfo & info)
{
	keyPressRelease(pos.x, pos.y, GetWidth(), true);
}

void TizenPort::OpenGLFrame::OnTouchPressed(const Control & src, const Point & pos, const TouchEventInfo & info)
{
	keyPressRelease(pos.x, pos.y, GetWidth(), true);
}

void TizenPort::OpenGLFrame::OnTouchReleased(const Control & src, const Point & pos, const TouchEventInfo & info)
{
	keyPressRelease(pos.x, pos.y, GetWidth(), false);
}

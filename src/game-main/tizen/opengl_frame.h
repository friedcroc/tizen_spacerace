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
#ifndef __1625b8e499fd3146865212e5ccf4fc07__
#define __1625b8e499fd3146865212e5ccf4fc07__

#include <FUi.h>

namespace TizenPort
{
	using Tizen::Graphics::Point;
	using Tizen::Ui::Control;
	using Tizen::Ui::TouchEventInfo;

	class OpenGLFrame : public Tizen::Ui::Controls::Frame,
						public Tizen::Ui::Controls::IFrameEventListener,
						public Tizen::Ui::ITouchEventListener
	{
	public:
		result OnInitializing() override;
		result OnTerminating() override;

		void OnFrameActivated(const Tizen::Ui::Controls::Frame & source) override;
		void OnFrameTerminating(const Tizen::Ui::Controls::Frame & source) override;

		void OnTouchCanceled(const Control & src, const Point & pos, const TouchEventInfo & info) override;
		void OnTouchFocusIn(const Control & src, const Point & pos, const TouchEventInfo & info) override;
		void OnTouchFocusOut(const Control & src, const Point & pos, const TouchEventInfo & info) override;
		void OnTouchMoved(const Control & src, const Point & pos, const TouchEventInfo & info) override;
		void OnTouchPressed(const Control & src, const Point & pos, const TouchEventInfo & info) override;
		void OnTouchReleased(const Control & src, const Point & pos, const TouchEventInfo & info) override;
	};
}

#endif

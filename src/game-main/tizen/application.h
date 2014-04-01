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
#ifndef __6fb0917922913ade569c16a93e5775fc__
#define __6fb0917922913ade569c16a93e5775fc__

#include <FBase.h>
#include <FApp.h>
#include <FGrpGlPlayer.h>

namespace TizenPort
{
	class OpenGLFrame;

	class Application : public Tizen::App::UiApp
	{
	public:
		Application();
		~Application();

		bool OnAppInitializing(Tizen::App::AppRegistry & appRegistry) override;
		bool OnAppTerminating(Tizen::App::AppRegistry & appRegistry, bool urgentTermination = false) override;

	private:
		OpenGLFrame * m_Frame;
		Tizen::Graphics::Opengl::GlPlayer * m_Player;
		Tizen::Graphics::Opengl::IGlRenderer * m_Renderer;

		void cleanup() noexcept;
	};
}

#endif

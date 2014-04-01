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
#include "../game_instance.h"
#include "application.h"
#include "opengl_renderer.h"
#include "opengl_frame.h"

/* TizenApplication */

TizenPort::Application::Application()
	: m_Frame(nullptr),
	  m_Player(nullptr),
	  m_Renderer(nullptr)
{
}

TizenPort::Application::~Application()
{
}

bool TizenPort::Application::OnAppInitializing(Tizen::App::AppRegistry & appRegistry)
{
	result r;

	(void)appRegistry;

	try
	{
		// Query OpenGL settings
		OpenGLInitOptions opt;
		GameInstance::instance()->configureOpenGL(opt);

		// Create OpenGL frame
		m_Frame = new OpenGLFrame;
		r = m_Frame->Construct();
		TryReturn(!IsFailed(r), r, "unable to create OpenGL frame.");

		// Register event listeners
		m_Frame->AddFrameEventListener(*m_Frame);
		m_Frame->AddTouchEventListener(*m_Frame);
		// m_Frame->AddKeyEventListener(*this);

		// Add OpenGL frame into the application
		r = AddFrame(*m_Frame);
		TryReturn(!IsFailed(r), r, "unable to add OpenGL frame into the application.");

		// Create OpenGL player
		m_Player = new Tizen::Graphics::Opengl::GlPlayer;
		r = m_Player->Construct(Tizen::Graphics::Opengl::EGL_CONTEXT_CLIENT_VERSION_2_X, m_Frame);
		TryReturn(!IsFailed(r), r, "unable to create OpenGL ES 2.0 player.");

		// Set desired frame rate
		m_Player->SetFps(60);

		// Configure the OpenGL player
		if (opt.alphaBits > 0 || opt.redBits + opt.greenBits + opt.blueBits > 16)
			r = m_Player->SetEglAttributePreset(Tizen::Graphics::Opengl::EGL_ATTRIBUTES_PRESET_ARGB8888);
		else
			r = m_Player->SetEglAttributePreset(Tizen::Graphics::Opengl::EGL_ATTRIBUTES_PRESET_RGB565);
		TryReturn(!IsFailed(r), r, "unable to set color depth for the OpenGL ES 2.0 player.");

		// Start the OpenGL player
		r = m_Player->Start();
		TryReturn(!IsFailed(r), r, "unable to start the OpenGL ES 2.0 player.");

		// Create the OpenGL renderer
		m_Renderer = new OpenGLRenderer;
		r = m_Player->SetIGlRenderer(m_Renderer);
		TryReturn(!IsFailed(r), r, "unable to activate the OpenGL ES 2.0 renderer.");
	}
	catch (const std::exception & e)
	{
		AppLogException(e.what());
		cleanup();
		return false;
	}

	AppLog("App initialization successful.");

	return true;
}

bool TizenPort::Application::OnAppTerminating(Tizen::App::AppRegistry & appRegistry, bool urgentTermination)
{
	cleanup();
	return true;
}

void TizenPort::Application::cleanup() noexcept
{
	try
	{
		if (m_Player)
			m_Player->Stop();

		delete m_Renderer;
		m_Renderer = NULL;

		delete m_Player;
		m_Player = NULL;
	}
	catch (const std::exception & e)
	{
		AppLogException(e.what());
	}
}

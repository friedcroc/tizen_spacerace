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
#ifndef __9c737b5fd1ba40f53025d5221a5f0032__
#define __9c737b5fd1ba40f53025d5221a5f0032__

#include "../cxx-util/macros.h"
#include "../gl-wrappers/gl_resource_manager.h"
#include "mouse_button.h"
#include "key_code.h"
#include "opengl_init_options.h"
#include <cstdint>
#include <cassert>

/**
 * Base class for games created using this framework.
 *
 * When creating a new game, you have to subclass from this class and override callback methods.
 * Then use the special macro `GAME_MAIN_CLASS` in the C++ source (**not header**!) file:
 *
 * @code
 * class MyGame : public GameInstance
 * {
 *    void init() {}
 *    void cleanup() {}
 *    void runFrame() {}
 * };
 * GAME_MAIN_CLASS(MyGame)
 * @endcode
 */
class GameInstance
{
public:
	/** Constructor. */
	GameInstance() noexcept;

	/** Destructor. */
	~GameInstance() noexcept;

	/**
	 * Returns pointer to the instance of the game.
	 * @return Pointer to the instance of the game.
	 */
	static GameInstance * instance() noexcept;

	/**
	 * Returns pointer to the OpenGL resource manager.
	 * @return Pointer to the OpenGL resource manager.
	 */
	const GL::ResourceManagerPtr & resourceManager() const;

	/**
	 * Returns width of the viewport.
	 * @return Width of the viewport.
	 */
	inline int viewportWidth() const noexcept { return m_ViewportWidth; }

	/**
	 * Returns height of the viewport.
	 * @return Height of the viewport.
	 */
	inline int viewportHeight() const noexcept { return m_ViewportHeight; }

	/** @cond */
	inline void setViewportSize_(int w, int h) { m_ViewportWidth = w; m_ViewportHeight = h; }
	/** @endcond */

	/**
	 * Initializes the game.
	 * This method is called once by the framework to initialize the game.
	 * This method should be overriden in child classes.
	 */
	virtual void init() = 0;

	/**
	 * Releases resources acquired by the game.
	 * This method is called once by the framework to deinitialize the game.
	 * This method should be overriden in child classes.
	 */
	virtual void cleanup() = 0;

	/** @cond */
	void cleanup_();
	/** @endcond */

	/**
	 * Runs one game frame.
	 * This method is called by the framework each frame to update the game, render it's contents, etc.
	 * This method should be overriden in child classes.
	 */
	virtual void runFrame() = 0;

	/** @cond */
	void runFrame_();
	/** @endcond */

	/**
	 * Allows game to modify OpenGL initialization options.
	 * @param options Reference to OpenGL initialization options that could be modified by the game.
	 * @warning This method is called before the init() method.
	 */
	virtual void configureOpenGL(OpenGLInitOptions & options);

	/**
	 * Called when user presses mouse button over the viewport.
	 * @param x X coordinate where user has pressed the button.
	 * @param y Y coordinate where user has pressed the button.
	 * @param button Button that has been pressed.
	 */
	virtual void onMouseButtonDown(int x, int y, Sys::MouseButton button);

	/**
	 * Called when user releases mouse button over the viewport.
	 * @param x X coordinate where user has released the button.
	 * @param y Y coordinate where user has released the button.
	 * @param button Button that has been released.
	 */
	virtual void onMouseButtonUp(int x, int y, Sys::MouseButton button);

	/**
	 * Called when user moves the mouse over the viewport.
	 * @param x X coordinate of mouse.
	 * @param y Y coordinate of mouse.
	 */
	virtual void onMouseMove(int x, int y);

	/**
	 * Called when user presses key on the keyboard.
	 * @param key Key code.
	 */
	virtual void onKeyPress(Sys::KeyCode key);

	/**
	 * Called when user releases key on the keyboard.
	 * @param key Key code.
	 */
	virtual void onKeyRelease(Sys::KeyCode key);

	/**
	 * Called when user enters text on the keyboard.
	 * @param ch UTF-16 character code.
	 */
	virtual void onCharInput(uint16_t ch);

private:
	mutable GL::ResourceManagerPtr m_ResourceManager;
	bool m_ResourceManagerDestroyed;
	int m_ViewportWidth;
	int m_ViewportHeight;

	GameInstance(const GameInstance &) = delete;
	GameInstance & operator=(const GameInstance &) = delete;
};

/**
 * Declares main class for the game.
 * @param CLASS Name of the main class.
 * @see GameInstance.
 */
#define GAME_MAIN_CLASS(CLASS) \
	static CLASS c9737b5fd1ba40f53025d5221a5f0032; \
	extern "C" { \
		void * c9737b5fd() { return static_cast<GameInstance *>(&c9737b5fd1ba40f53025d5221a5f0032); } \
	}

#endif

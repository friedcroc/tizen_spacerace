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
#ifndef __c755843ef2a1c2e5fd352e45fc7bc65f__
#define __c755843ef2a1c2e5fd352e45fc7bc65f__

/** Options for OpenGL initialization. */
struct OpenGLInitOptions
{
	/**
	 * Desired width of the viewport, in pixels.
	 * @note Depending on the platform, real width of the viewport may differ.
	 */
	int desiredWidth = 1024;

	/**
	 * Desired height of the viewport, in pixels.
	 * @note Depending on the platform, real height of the viewport may differ.
	 */
	int desiredHeight = 768;

	/**
	 * Set to *true* to request fullscreen rendering.
	 * @note Depending on the platform, this option may or may not be honored.
	 */
	bool fullscreen = false;

	/**
	 * Set to *true* to request vsync.
	 * @note Depending on the platform, this option may or may not be honored.
	 */
	bool vsync = true;

	/**
	 * Set to *true* to request full resolution on high-density displays.
	 * @note Depending on the platform, this option may or may not be honored.
	 */
	bool fullResolution = true;

	/**
	 * Desired number of bits in the red channel of the color buffer.
	 * @note Depending on the platform, real number of bits in the red channel may differ.
	 */
	int redBits = 8;

	/**
	 * Desired number of bits in the green channel of the color buffer.
	 * @note Depending on the platform, real number of bits in the green channel may differ.
	 */
	int greenBits = 8;

	/**
	 * Desired number of bits in the blue channel of the color buffer.
	 * @note Depending on the platform, real number of bits in the blue channel may differ.
	 */
	int blueBits = 8;

	/**
	 * Desired number of bits in the alpha channel of the color buffer.
	 * @note Depending on the platform, real number of bits in the alpha channel may differ.
	 */
	int alphaBits = 8;

	/**
	 * Desired number of bits per component in the depth buffer.
	 * @note Depending on the platform, real number of bits per depth component may differ.
	 */
	int depthBits = 0;

	/**
	 * Desired number of bits per component in the stencil buffer.
	 * @note Depending on the platform, real number of bits per stencil component may differ.
	 */
	int stencilBits = 0;
};

#endif

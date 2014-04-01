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
#include "gl_error.h"
#include <iomanip>

#ifndef NDEBUG

std::ostream & operator<<(std::ostream & s, GL::Enum value)
{
	switch (value)
	{
	case GL::FALSE: break;
	case GL::TRUE: break;
	#define GL_CONSTANT_(X, Y) case Y: s << "GL_" << #X; return s;
	#include "gl_constants.h"
	#undef GL_CONSTANT_
	}
	s << static_cast<int>(value);
	return s;
}

std::string GL::decodeGLClearMask_(GL::Bitfield mask)
{
	const char * prefix = "";
	std::stringstream ss;

	if (mask & GL::COLOR_BUFFER_BIT)
	{
		ss << prefix << "GL_COLOR_BUFFER_BIT";
		prefix = " | ";
	}

	if (mask & GL::DEPTH_BUFFER_BIT)
	{
		ss << prefix << "GL_DEPTH_BUFFER_BIT";
		prefix = " | ";
	}

	if (mask & GL::STENCIL_BUFFER_BIT)
	{
		ss << prefix << "GL_STENCIL_BUFFER_BIT";
		prefix = " | ";
	}

	mask &= ~static_cast<GL::Bitfield>(GL::COLOR_BUFFER_BIT);
	mask &= ~static_cast<GL::Bitfield>(GL::DEPTH_BUFFER_BIT);
	mask &= ~static_cast<GL::Bitfield>(GL::STENCIL_BUFFER_BIT);
	if (mask != 0)
		ss << prefix << "0x" << std::hex << mask;

	return ss.str();
}

#endif

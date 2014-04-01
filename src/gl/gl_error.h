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
#ifndef __1c6923b29c9f8c0109f1dd564176a2ae__
#define __1c6923b29c9f8c0109f1dd564176a2ae__

#include "gl.h"
#include <sstream>
#include <iostream>
#include <string>

#ifdef NDEBUG
 #define CHECK_GL_LOCATION(name, var, location)
 #define CHECK_GL_ERROR0(name)
 #define CHECK_GL_ERROR1(name, p)
 #define CHECK_GL_ERROR2(name, p1, p2)
 #define CHECK_GL_ERROR3(name, p1, p2, p3)
 #define CHECK_GL_ERROR4(name, p1, p2, p3, p4)
 #define CHECK_GL_ERROR5(name, p1, p2, p3, p4, p5)
 #define CHECK_GL_ERROR6(name, p1, p2, p3, p4, p5, p6)
 #define CHECK_GL_ERROR7(name, p1, p2, p3, p4, p5, p6, p7)
 #define CHECK_GL_ERROR8(name, p1, p2, p3, p4, p5, p6, p7, p8)
 #define CHECK_GL_ERROR9(name, p1, p2, p3, p4, p5, p6, p7, p8, p9)
 #define CHECK_GLCLEAR_ERROR(name, p)
#else
 #define CHECK_GL_LOCATION(name, var, location) \
	{ \
		if (location < 0) \
			std::clog << #name << "(\"" << var << "\") returned " << location << '.' << std::endl; \
	}
 #define CHECK_GL_ERROR_(name, params) \
	{ \
		GL::Enum err = GL::getError(); \
		if (err != GL::NO_ERROR) \
			std::clog << #name << '(' << params << "): " << err << '.' << std::endl; \
	}
 #define CHECK_GL_ERROR0(name) CHECK_GL_ERROR_(name, "")
 #define CHECK_GL_ERROR1(name, p) CHECK_GL_ERROR_(name, p)
 #define CHECK_GL_ERROR2(name, p1, p2) CHECK_GL_ERROR_(name, p1 << ", " << p2)
 #define CHECK_GL_ERROR3(name, p1, p2, p3) CHECK_GL_ERROR_(name, p1 << ", " << p2 << ", " << p3)
 #define CHECK_GL_ERROR4(name, p1, p2, p3, p4) CHECK_GL_ERROR_(name, p1 << ", " << p2 << ", " << p3 << ", " << p4)
 #define CHECK_GL_ERROR5(name, p1, p2, p3, p4, p5) CHECK_GL_ERROR_(name, p1 << ", " << p2 << ", " << p3 << ", " << p4 << ", " << p5)
 #define CHECK_GL_ERROR6(name, p1, p2, p3, p4, p5, p6) CHECK_GL_ERROR_(name, p1 << ", " << p2 << ", " << p3 << ", " << p4 << ", " << p5 << ", " << p6)
 #define CHECK_GL_ERROR7(name, p1, p2, p3, p4, p5, p6, p7) CHECK_GL_ERROR_(name, p1 << ", " << p2 << ", " << p3 << ", " << p4 << ", " << p5 << ", " << p6 << ", " << p7)
 #define CHECK_GL_ERROR8(name, p1, p2, p3, p4, p5, p6, p7, p8) CHECK_GL_ERROR_(name, p1 << ", " << p2 << ", " << p3 << ", " << p4 << ", " << p5 << ", " << p6 << ", " << p7 << ", " << p8)
 #define CHECK_GL_ERROR9(name, p1, p2, p3, p4, p5, p6, p7, p8, p9) CHECK_GL_ERROR_(name, p1 << ", " << p2 << ", " << p3 << ", " << p4 << ", " << p5 << ", " << p6 << ", " << p7 << ", " << p8 << ", " << p9)
 #define CHECK_GLCLEAR_ERROR(name, p) CHECK_GL_ERROR_(name, GL::decodeGLClearMask_(p))
 std::ostream & operator<<(std::ostream & s, GL::Enum value);
 namespace GL {
	std::string decodeGLClearMask_(GL::Bitfield mask);
 }
#endif

#endif

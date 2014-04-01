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
#ifndef __adf60d163684629456ca171675cc503e__
#define __adf60d163684629456ca171675cc503e__

#include "common.h"
#include <cstddef>

class mat4
{
public:
	inline mat4() {}

	inline mat4(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j,
		float k, float l, float n, float o, float p, float q)
	{
		m[0]  = a; m[1]  = e; m[2]  = i; m[3]  = n;
		m[4]  = b; m[5]  = f; m[6]  = j; m[7]  = o;
		m[8]  = c; m[9]  = g; m[10] = k; m[11] = p;
		m[12] = d; m[13] = h; m[14] = l; m[15] = q;
	}

	inline static mat4 identity() { return mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1); }

	static mat4 translation(float x, float y, float z);

	static mat4 rotationX(float radians);
	static mat4 rotationY(float radians);
	static mat4 rotationZ(float radians);

	static mat4 scaling(float x, float y, float z);

	static mat4 ortho(float left, float right, float bottom, float top, float zNear, float zFar);

	mat4 operator*(const mat4 & b) const;

	inline const float & operator[](size_t index) const { assert(index < 16); return m[index]; }
	inline float & operator[](size_t index) { assert(index < 16); return m[index]; }

private:
	float m[16];
};

#endif

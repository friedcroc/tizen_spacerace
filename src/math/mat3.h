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
#ifndef __0dd87e9dfdea657e8be233b5836821d0__
#define __0dd87e9dfdea657e8be233b5836821d0__

#include "common.h"
#include "vec2.h"
#include <cstddef>

class mat3
{
public:
	inline mat3() {}

	inline mat3(float a, float b, float c, float d, float e, float f, float g, float h, float i)
		{ m[0] = a; m[1] = d; m[2] = g; m[3] = b; m[4] = e; m[5] = h; m[6] = c; m[7] = f; m[8] = i; }

	inline static mat3 identity() { return mat3(1, 0, 0, 0, 1, 0, 0, 0, 1); }

	inline static mat3 translation(const vec2 & v) { return mat3(1, 0, v.x(), 0, 1, v.y(), 0, 0, 1); }
	inline static mat3 translation(float x, float y) { return mat3(1, 0, x, 0, 1, y, 0, 0, 1); }

	inline static mat3 scaling(const vec2 & v) { return mat3(v.x(), 0, 0, 0, v.y(), 0, 0, 0, 1); }
	inline static mat3 scaling(float x, float y) { return mat3(x, 0, 0, 0, y, 0, 0, 0, 1); }

	static mat3 rotation(float radians);
	static mat3 rotationX(float radians);
	static mat3 rotationY(float radians);
	static mat3 rotationZ(float radians);

	inline vec2 translation() const { return vec2(m[6], m[7]); }
	inline float translationX() const { return m[6]; }
	inline float translationY() const { return m[7]; }

	inline vec2 scale() const { return vec2(scaleX(), scaleY()); }
	inline float scaleX() const { return signf(m[0]) * sqrtf(m[0] * m[0] + m[3] * m[3]); }
	inline float scaleY() const { return signf(m[4]) * sqrtf(m[1] * m[1] + m[4] * m[4]); }

	inline float rotation() const { return atan2f(m[1], m[4]); }

	mat3 operator*(const mat3 & b) const;

	float determinant() const;

	inline const float & operator[](size_t index) const { assert(index < 9); return m[index]; }
	inline float & operator[](size_t index) { assert(index < 9); return m[index]; }

private:
	float m[9];
};

vec2 transform(const mat3 & m, const vec2 & v);

#endif

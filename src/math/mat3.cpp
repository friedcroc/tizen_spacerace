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
#include "mat3.h"

mat3 mat3::rotation(float radians)
{
	float s = sinf(radians);
	float c = cosf(radians);
	return mat3(
		c, -s,  0,
		s,  c,  0,
		0,  0,  1
	);
}

mat3 mat3::rotationX(float radians)
{
	float s = sinf(radians);
	float c = cosf(radians);
	return mat3(
		1,  0,  0,
		0,  c, -s,
		0,  s,  c
	);
}

mat3 mat3::rotationY(float radians)
{
	float s = sinf(radians);
	float c = cosf(radians);
	return mat3(
		 c,  0,  s,
		 0,  1,  0,
		-s,  0,  c
	);
}

mat3 mat3::rotationZ(float radians)
{
	float s = sinf(radians);
	float c = cosf(radians);
	return mat3(
		 c,  s,  0,
		-s,  c,  0,
		 0,  0,  1
	);
}

mat3 mat3::operator*(const mat3 & b) const
{
	const float * m1 = m, * m2 = b.m;
	mat3 r;

	r.m[0] = m1[0] * m2[0] + m1[3] * m2[1] + m1[6] * m2[2];
	r.m[1] = m1[1] * m2[0] + m1[4] * m2[1] + m1[7] * m2[2];
	r.m[2] = m1[2] * m2[0] + m1[5] * m2[1] + m1[8] * m2[2];

	r.m[3] = m1[0] * m2[3] + m1[3] * m2[4] + m1[6] * m2[5];
	r.m[4] = m1[1] * m2[3] + m1[4] * m2[4] + m1[7] * m2[5];
	r.m[5] = m1[2] * m2[3] + m1[5] * m2[4] + m1[8] * m2[5];

	r.m[6] = m1[0] * m2[6] + m1[3] * m2[7] + m1[6] * m2[8];
	r.m[7] = m1[1] * m2[6] + m1[4] * m2[7] + m1[7] * m2[8];
	r.m[8] = m1[2] * m2[6] + m1[5] * m2[7] + m1[8] * m2[8];

	return r;
}

float mat3::determinant() const
{
	return
		m[0] * m[4] * m[8] +
		m[1] * m[5] * m[6] +
		m[2] * m[3] * m[7] -
		m[2] * m[4] * m[6] -
		m[0] * m[5] * m[7] -
		m[1] * m[3] * m[8];
}

vec2 transform(const mat3 & m, const vec2 & v)
{
	return vec2(
		v.x() * m[0] + v.y() * m[3] + m[6],
		v.x() * m[1] + v.y() * m[4] + m[7]
	);
}

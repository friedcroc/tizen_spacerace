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
#include "mat4.h"

mat4 mat4::translation(float x, float y, float z)
{
	return mat4(
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	);
}

mat4 mat4::rotationX(float radians)
{
	float s = sinf(radians);
	float c = cosf(radians);
	return mat4(
		1,  0,  0, 0,
		0,  c, -s, 0,
		0,  s,  c, 0,
		0,  0,  0, 1
	);
}

mat4 mat4::rotationY(float radians)
{
	float s = sinf(radians);
	float c = cosf(radians);
	return mat4(
		 c,  0,  s, 0,
		 0,  1,  0, 0,
		-s,  0,  c, 0,
		 0,  0,  0, 1
	);
}

mat4 mat4::rotationZ(float radians)
{
	float s = sinf(radians);
	float c = cosf(radians);
	return mat4(
		 c,  s,  0, 0,
		-s,  c,  0, 0,
		 0,  0,  1, 0,
		 0,  0,  0, 1
	);
}

mat4 mat4::scaling(float x, float y, float z)
{
	return mat4(
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1
	);
}

mat4 mat4::ortho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	float rw = 1.0f / (right - left);
	float rh = 1.0f / (top - bottom);
	float rd = 1.0f / (zFar - zNear);

	float tx = -(right + left) * rw;
	float ty = -(top + bottom) * rh;
	float tz = -(zFar + zNear) * rd;

	return mat4(
		2 * rw,	0,		0,			tx,
		0,		2 * rh,	0,			ty,
		0,		0,		-2 * rd,	tz,
		0,		0,		0,			1
	);
}

mat4 mat4::operator*(const mat4 & b) const
{
	const float * m1 = m, * m2 = b.m;
	mat4 r;

	r.m[0]  = m1[0] * m2[ 0] + m1[4] * m2[ 1] + m1[ 8] * m2[ 2] + m1[12] * m2[ 3];
	r.m[1]  = m1[1] * m2[ 0] + m1[5] * m2[ 1] + m1[ 9] * m2[ 2] + m1[13] * m2[ 3];
	r.m[2]  = m1[2] * m2[ 0] + m1[6] * m2[ 1] + m1[10] * m2[ 2] + m1[14] * m2[ 3];
	r.m[3]  = m1[3] * m2[ 0] + m1[7] * m2[ 1] + m1[11] * m2[ 2] + m1[15] * m2[ 3];
	r.m[4]  = m1[0] * m2[ 4] + m1[4] * m2[ 5] + m1[ 8] * m2[ 6] + m1[12] * m2[ 7];
	r.m[5]  = m1[1] * m2[ 4] + m1[5] * m2[ 5] + m1[ 9] * m2[ 6] + m1[13] * m2[ 7];
	r.m[6]  = m1[2] * m2[ 4] + m1[6] * m2[ 5] + m1[10] * m2[ 6] + m1[14] * m2[ 7];
	r.m[7]  = m1[3] * m2[ 4] + m1[7] * m2[ 5] + m1[11] * m2[ 6] + m1[15] * m2[ 7];
	r.m[8]  = m1[0] * m2[ 8] + m1[4] * m2[ 9] + m1[ 8] * m2[10] + m1[12] * m2[11];
	r.m[9]  = m1[1] * m2[ 8] + m1[5] * m2[ 9] + m1[ 9] * m2[10] + m1[13] * m2[11];
	r.m[10] = m1[2] * m2[ 8] + m1[6] * m2[ 9] + m1[10] * m2[10] + m1[14] * m2[11];
	r.m[11] = m1[3] * m2[ 8] + m1[7] * m2[ 9] + m1[11] * m2[10] + m1[15] * m2[11];
	r.m[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[ 8] * m2[14] + m1[12] * m2[15];
	r.m[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[ 9] * m2[14] + m1[13] * m2[15];
	r.m[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15];
	r.m[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15];

	return r;
}

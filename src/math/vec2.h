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
#ifndef __443a134ac7bf021dc463f4439c09f349__
#define __443a134ac7bf021dc463f4439c09f349__

#include "common.h"

class vec2
{
public:
	inline vec2() : X(0), Y(0) {}
	inline vec2(float x_, float y_) : X(x_), Y(y_) {}

	inline float x() const { return X; }
	inline float y() const { return Y; }

	inline vec2 operator-() const { return vec2(-X, -Y); }

	inline vec2 operator+(const vec2 & b) const { return vec2(X + b.X, Y + b.Y); }
	inline vec2 operator-(const vec2 & b) const { return vec2(X - b.X, Y - b.Y); }

	inline vec2 operator+(float b) const { return vec2(X + b, Y + b); }
	inline vec2 operator-(float b) const { return vec2(X - b, Y - b); }
	inline vec2 operator*(float b) const { return vec2(X * b, Y * b); }
	inline vec2 operator/(float b) const { return vec2(X / b, Y / b); }

	inline vec2 & operator+=(const vec2 & b) { X += b.X; Y += b.Y; return *this; }
	inline vec2 & operator-=(const vec2 & b) { X -= b.X; Y -= b.Y; return *this; }

	inline vec2 & operator+=(float b) { X += b; Y += b; return *this; }
	inline vec2 & operator-=(float b) { X -= b; Y -= b; return *this; }
	inline vec2 & operator*=(float b) { X *= b; Y *= b; return *this; }
	inline vec2 & operator/=(float b) { X /= b; Y /= b; return *this; }

	inline float magnitude() const { return X * X + Y * Y; }
	inline float length() const { return sqrtf(X * X + Y * Y); }

	inline vec2 normalized() const { float l = 1.0f / length(); return vec2(X * l, Y * l); }

private:
	float X;
	float Y;
};

inline vec2 operator+(float a, const vec2 & b) { return vec2(a + b.x(), a + b.y()); }
inline vec2 operator-(float a, const vec2 & b) { return vec2(a - b.x(), a - b.y()); }
inline vec2 operator*(float a, const vec2 & b) { return vec2(a * b.x(), a * b.y()); }
inline vec2 operator/(float a, const vec2 & b) { return vec2(a - b.x(), a - b.y()); }

inline float dot(const vec2 & a, const vec2 & b) { return a.x() * b.x() + a.y() * b.y(); }
inline float cross(const vec2 & a, const vec2 & b) { return a.x() * b.y() - a.y() * b.x(); }
inline vec2 cross(const vec2 & a, float b) { return vec2(a.y() * b, -a.x() * b); }
inline vec2 cross(float a, const vec2 & b) { return vec2(-a * b.y(), a * b.x()); }

inline vec2 lerp(const vec2 & a, const vec2 & b, float t) { return a + t * (b - a); }

vec2 rotate(const vec2 & vector, float radians, const vec2 & pivot = vec2());

float radiansBetween(const vec2 & vec1, const vec2 & vec2);
inline float degreesBetween(const vec2 & vec1, const vec2 & vec2) { return rad2deg(radiansBetween(vec1, vec2)); }

#endif
